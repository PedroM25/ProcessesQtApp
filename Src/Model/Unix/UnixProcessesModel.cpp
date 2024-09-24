#include "UnixProcessesModel.h"

#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include <dirent.h>
#include <pwd.h>
#include <signal.h>
#include <cstring>

#include <QDebug>

#include "ProcessInfo.h"

UnixProcessesModel::UnixProcessesModel()
{
	m_procFilter = std::make_unique<CommandProcessesFilter>(); // could be set with "setProcessesFilter()"
	m_procDiff = ProcessesDiff{};
}

UnixProcessesModel::~UnixProcessesModel()
{
	if (m_thread.joinable())
	{
		m_keepThreadAlive = false;
		m_thread.join();
	}
}

// Function to read the contents of a file into a string
std::string UnixProcessesModel::readFile(const std::string& path) const
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

// Function to get the username from the UID
std::string UnixProcessesModel::getUsernameFromUID(uid_t uid) const
{
	struct passwd* pw = getpwuid(uid);
	return (pw != nullptr) ? std::string(pw->pw_name) : std::to_string(uid);
}

void closeDirectory(DIR* dir)
{
	closedir(dir);
};

std::set<ProcessInfo> UnixProcessesModel::getAllProcessesInfo() const
{
	std::set<ProcessInfo> ret{};

	using dirUniquePtr = std::unique_ptr<DIR, decltype(&closeDirectory)>;
	dirUniquePtr procDir = dirUniquePtr(opendir("/proc"), &closeDirectory);

	if (procDir == nullptr)
	{
		qCritical() << "Error opening /proc directory";
		return ret;
	}

	struct dirent* entry;
	while ((entry = readdir(procDir.get())) != nullptr)
	{
		// Check if the directory name is a number (i.e., a process ID)
		if (entry->d_type == DT_DIR && isdigit(entry->d_name[0]))
		{
			std::string pid = entry->d_name;

			// Read the UID from /proc/[pid]/status
			std::string statusPath = "/proc/" + pid + "/status";
			std::string statusContent = readFile(statusPath);
			if (statusContent.empty())
			{
				continue;
			}

			std::istringstream statusStream(statusContent);
			std::string line;
			uid_t uid = -1;
			while (std::getline(statusStream, line))
			{
				if (line.compare(0, 4, "Uid:") == 0)
				{
					std::istringstream uidStream(line.substr(5));
					uidStream >> uid;
					break;
				}
			}
			if (uid == -1)
			{
				continue;
			}

			// Get the username from the UID
			std::string username = getUsernameFromUID(uid);

			// Read the command from /proc/[pid]/cmdline
			std::string cmdPath = "/proc/" + pid + "/cmdline";
			std::string cmdContent = readFile(cmdPath);
			if (cmdContent.empty())
			{ // most likely a kernel thread
				cmdPath = "/proc/" + pid + "/comm";
				cmdContent = readFile(cmdPath);
				cmdContent.erase(std::remove(cmdContent.begin(), cmdContent.end(), '\n'), cmdContent.end());
				cmdContent = "[" + cmdContent + "]";
			}
			else
			{
				std::replace(cmdContent.begin(), cmdContent.end(), '\0', ' '); // Replace null characters with spaces
			}

			// Print the PID, username, and command
			// qDebug() << "PID: " << pid.c_str() << ", User: " << username.c_str() << ", Command: " <<
			// cmdContent.c_str(); add to vector
			ret.insert({std::stoi(pid), username, cmdContent});
		}
	}

	return ret;
}

void UnixProcessesModel::threadFunc()
{
	while (m_keepThreadAlive)
	{
		auto tempAllProcessesInfo = getAllProcessesInfo();
		AddRemoveProcsStruct diffRes{};
		int currNumProcesses{};
		{
			std::lock_guard<std::mutex> lock{m_setCallback};

			m_allProcessesInfo = std::move(tempAllProcessesInfo);
			diffRes = m_procDiff.calculateDiff(m_procFilter->performFiltering(m_allProcessesInfo));
			currNumProcesses = m_allProcessesInfo.size();
		}
		m_callback(std::move(diffRes), currNumProcesses);
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
	}
}

void UnixProcessesModel::startGetProcessesInfoThread(const std::function<void(AddRemoveProcsStruct, int)> cb)
{
	m_callback = cb;
	std::thread te(&UnixProcessesModel::threadFunc, this);
	m_thread = std::move(te);
}

int UnixProcessesModel::killProcess(pid_t pid) const
{
	qDebug() << "Real UID: " << getuid() << ", Effective UID: " << geteuid();
	qDebug() << "PID to kill: " << pid;
	auto killRes = kill(pid, SIGTERM);
	if (killRes != 0){
		qDebug() << "Process kill failed: " << std::strerror(errno);
	}
	return killRes;
}

void UnixProcessesModel::setFilter(const std::string filter)
{
	m_procFilter->setFilter(filter);
	AddRemoveProcsStruct diffRes{};
	int currNumProcesses{};
	{
		std::lock_guard<std::mutex> lock{m_setCallback};
		
		diffRes = m_procDiff.calculateDiff(m_procFilter->performFiltering(m_allProcessesInfo));
		currNumProcesses = m_allProcessesInfo.size();
	}
	m_callback(std::move(diffRes), currNumProcesses);
}
