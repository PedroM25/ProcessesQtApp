#pragma once
#include <thread>
#include <atomic>
#include <mutex>

#include "IProcessesModel.h"
#include "CommandProcessesFilter.h"
#include "ProcessesDiff.h"

class ProcessesFilter;

class UnixProcessesModel : public IProcessesModel
{
public:
	void startGetProcessesInfoThread(const std::function<void(AddRemoveProcsStruct, int)> cb) override;
	int killProcess(pid_t pid) const override;
	void setFilter(const std::string filter) override;

	~UnixProcessesModel();
	UnixProcessesModel();
	UnixProcessesModel(const UnixProcessesModel& other) = delete;
	UnixProcessesModel& operator=(const UnixProcessesModel& other) = delete;
	UnixProcessesModel(UnixProcessesModel&& other) = default;
	UnixProcessesModel& operator=(UnixProcessesModel&& other) = default;

private:
	void threadFunc();
	std::set<ProcessInfo> getAllProcessesInfo() const;
	std::string readFile(const std::string& path) const;
	std::string getUsernameFromUID(uid_t uid) const;

private:
	std::thread m_thread;
	std::atomic<bool> m_keepThreadAlive{true};
	std::unique_ptr<ProcessesFilter> m_procFilter;
	ProcessesDiff m_procDiff;
	std::function<void(AddRemoveProcsStruct, int)> m_callback;
	std::mutex m_setCallback;
	std::set<ProcessInfo> m_allProcessesInfo;
};