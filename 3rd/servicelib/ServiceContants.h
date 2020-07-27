// Copyright (c) 2016 Marius Bancila
// License: CPOL http://www.codeproject.com/info/cpol10.aspx

#pragma once

#include <tchar.h>
#include <windows.h>
#include <Winsvc.h>

#ifdef UNICODE
#define ServiceString   std::wstring
#else
#define ServiceString   std::string
#endif

enum class ServiceStatus 
{
   Unknown     = 0,
   Stopped     = SERVICE_STOPPED,
   Starting    = SERVICE_START_PENDING,
   Stopping    = SERVICE_STOP_PENDING,
   Running     = SERVICE_RUNNING,
   Continuing  = SERVICE_CONTINUE_PENDING,
   Pausing     = SERVICE_PAUSE_PENDING,
   Paused      = SERVICE_PAUSED
};

enum class ServiceControls
{
   // The service can be stopped.
   Stop                                = SERVICE_ACCEPT_STOP,
   // The service can be paused and continued.
   PauseAndContinue                    = SERVICE_ACCEPT_PAUSE_CONTINUE,
   // The service can reread its startup parameters without being stopped and restarted.
   ChangeParams                        = SERVICE_ACCEPT_PARAMCHANGE,
   // The service is a network component that can accept changes in its binding without being stopped and restarted.
   ChangeBindings                      = SERVICE_ACCEPT_NETBINDCHANGE,
   // The service can perform pre-shutdown tasks.
   PreShutdown                         = SERVICE_ACCEPT_PRESHUTDOWN,

   // The service is notified when system shutdown occurs.
   ShutdownNotification                = SERVICE_ACCEPT_SHUTDOWN,
   // The service is notified when the computer's hardware profile has changed.
   HardwareProfileChangedNotification  = SERVICE_ACCEPT_HARDWAREPROFILECHANGE,
   // The service is notified when the computer's power status has changed.
   PowerChangedNotification            = SERVICE_ACCEPT_POWEREVENT,
   // The service is notified when the computer's session status has changed.
   SessionChangedNotification          = SERVICE_ACCEPT_SESSIONCHANGE,
   // The service is notified when an event for which the service has registered occurs. 
   TriggerEventNotification            = SERVICE_ACCEPT_TRIGGEREVENT,
   // The service is notified when the system time has changed
   TimeChangeNotification              = SERVICE_ACCEPT_TIMECHANGE,
   // The services is notified when the user initiates a reboot.
   UserModeNotification                = 0x00000800, //SERVICE_ACCEPT_USERMODEREBOOT
};

enum class ServiceType
{
   // A Kernel device driver such as a hard disk or other low-level hardware device driver.
   KernelDriver      = SERVICE_KERNEL_DRIVER,

   // A file system driver, which is also a Kernel device driver.
   FileSystemDriver  = SERVICE_FILE_SYSTEM_DRIVER,

   // A service for a hardware device that requires its own driver.
   Adapter           = SERVICE_ADAPTER,

   // A file system driver used during startup to determine the file systems present on the system.
   RecognizerDriver  = SERVICE_RECOGNIZER_DRIVER,

   // A Win32 service that runs in its own process.
   Win32OwnProcess   = SERVICE_WIN32_OWN_PROCESS,

   // A Win32 service that can share a process with other Win32 services.
   Win32ShareProcess = SERVICE_WIN32_SHARE_PROCESS,

   // A service that can communicate with the desktop.
   InteractiveDriver = SERVICE_INTERACTIVE_PROCESS,

   Driver            = SERVICE_DRIVER,
   Win32             = SERVICE_WIN32,
   All               = SERVICE_TYPE_ALL
};

enum class ServiceStartType
{
   // A device driver started by the system loader. This value is valid only for driver services.
   Boot     = SERVICE_BOOT_START,

   // A device driver started by the IoInitSystem function. This value is valid only for driver services.
   System   = SERVICE_SYSTEM_START,

   // A service started automatically by the service control manager during system startup.
   Auto     = SERVICE_AUTO_START,

   // A service started by the service control manager when a process calls the StartService function.
   Demand   = SERVICE_DEMAND_START,

   // A service that cannot be started. Attempts to start the service result in the error code ERROR_SERVICE_DISABLED.
   Disabled = SERVICE_DISABLED,
};

enum class ServiceErrorControl
{
   // The startup program ignores the error and continues the startup operation.
   Ignore   = SERVICE_ERROR_IGNORE,

   // The startup program logs the error in the event log and continues the startup operation.
   Normal   = SERVICE_ERROR_NORMAL,

   // The startup program logs the error in the event log. If the last-known good configuration is being started, the startup operation continues. 
   // Otherwise, the system is restarted with the last-known-good configuration.
   Severe   = SERVICE_ERROR_SEVERE,

   // The startup program logs the error in the event log, if possible. If the last-known good configuration is being started, the startup operation fails. 
   // Otherwise, the system is restarted with the last-known good configuration.
   Critical = SERVICE_ERROR_CRITICAL,
};

enum class ServiceState
{
   // Services that are in the following states: SERVICE_START_PENDING, SERVICE_STOP_PENDING, SERVICE_RUNNING, SERVICE_CONTINUE_PENDING, SERVICE_PAUSE_PENDING, and SERVICE_PAUSED.
   Active   = SERVICE_ACTIVE,

   // Services that are in the SERVICE_STOPPED state.
   Inactive = SERVICE_INACTIVE,

   // Combines the SERVICE_ACTIVE and SERVICE_INACTIVE states.
   All      = SERVICE_STATE_ALL
};

ServiceString ServiceStatusToString(ServiceStatus const status)
{
   switch (status)
   {
      case ServiceStatus::Stopped:     return _T("Stopped");
      case ServiceStatus::Starting:    return _T("Starting");
      case ServiceStatus::Stopping:    return _T("Stopping");
      case ServiceStatus::Running:     return _T("Running");
      case ServiceStatus::Continuing:  return _T("Continuing");
      case ServiceStatus::Pausing:     return _T("Pausing");
      case ServiceStatus::Paused:      return _T("Paused");
      default:                         return _T("Unknown");
   }
}

ServiceString ServiceTypeToString(ServiceType const type)
{
   switch (type)
   {
      case ServiceType::KernelDriver:        return _T("KernelDriver");
      case ServiceType::FileSystemDriver:    return _T("FileSystemDriver");
      case ServiceType::Adapter:             return _T("Adapter");
      case ServiceType::RecognizerDriver:    return _T("RecognizerDriver");
      case ServiceType::Win32OwnProcess:     return _T("Win32OwnProcess");
      case ServiceType::Win32ShareProcess:   return _T("Win32ShareProcess");
      case ServiceType::InteractiveDriver:   return _T("InteractiveDriver");
      case ServiceType::Driver:              return _T("Driver");
      case ServiceType::Win32:               return _T("Win32");
      case ServiceType::All:                 return _T("All");
      default:                               return _T("");
   }
}

ServiceString ServiceStartTypeToString(ServiceStartType const type)
{
   switch (type)
   {
      case ServiceStartType::Boot:     return _T("Boot");
      case ServiceStartType::System:   return _T("System");
      case ServiceStartType::Auto:     return _T("Auto");
      case ServiceStartType::Demand:   return _T("Demand");
      case ServiceStartType::Disabled: return _T("Disabled");
      default:                         return _T("");
   }
}

ServiceString ServiceErrorControlToString(ServiceErrorControl const control)
{
   switch (control)
   {
      case ServiceErrorControl::Ignore:      return _T("Ignore");
      case ServiceErrorControl::Normal:      return _T("Normal");
      case ServiceErrorControl::Severe:      return _T("Severe");
      case ServiceErrorControl::Critical:    return _T("Critical");
      default:                               return _T("");
   }
}
