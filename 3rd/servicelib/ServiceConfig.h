// Copyright (c) 2016 Marius Bancila
// License: CPOL http://www.codeproject.com/info/cpol10.aspx

#pragma once

#include "ServiceContants.h"

class ServiceConfig
{
   SC_HANDLE srvHandle;
   ServiceType type;
   ServiceStartType startType;
   ServiceErrorControl errorControl;
   ServiceString pathName;
   ServiceString loadOrderGroup;
   DWORD tagId;
   std::vector<ServiceString> dependencies;
   ServiceString startName;
   ServiceString displayName;
   ServiceString description;

public:
   ServiceType                      GetType() const               { return type; }
   ServiceStartType                 GetStartType() const          { return startType; }
   ServiceErrorControl              GetErrorControl() const       { return errorControl; }
   ServiceString                    GetBinaryPathName() const     { return pathName; }
   ServiceString                    GetLoadOrderingGroup() const  { return loadOrderGroup; }
   DWORD                            GetTagId() const              { return tagId; }
   std::vector<ServiceString> const GetDependencies() const       { return dependencies; }
   ServiceString                    GetStartName() const          { return startName; }
   ServiceString                    GetDisplayName() const        { return displayName; }
   ServiceString                    GetDescription() const        { return description; }

public:
   static ServiceConfig Create(SC_HANDLE const handle)
   {
      auto config = ServiceConfig{};
      config.srvHandle = handle;

      config.Refresh();

      return config;
   }

   bool ChangeStartType(ServiceStartType const type)
   {
      auto result = false;

      if (ChangeServiceConfig(
         srvHandle,
         SERVICE_NO_CHANGE,
         static_cast<DWORD>(type),
         SERVICE_NO_CHANGE,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr))
      {
         startType = type;
         result = true;
      }

      return result;
   }

   bool ChangeStartErrorControl(ServiceErrorControl const control)
   {
      auto result = false;

      if (ChangeServiceConfig(
         srvHandle,
         SERVICE_NO_CHANGE,
         SERVICE_NO_CHANGE,
         static_cast<DWORD>(control),         
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr))
      {
         errorControl = control;
         result = true;
      }

      return result;
   }

   bool ChangeDescription(ServiceString const newDescription)
   {
      auto result = false;

      auto sd = SERVICE_DESCRIPTION {};
      sd.lpDescription = const_cast<LPTSTR>(newDescription.c_str());

      if (ChangeServiceConfig2(srvHandle, SERVICE_CONFIG_DESCRIPTION, &sd))
      {
         description = newDescription;
         result = true;
      }

      return result;
   }

   void Refresh()
   {
      auto bytesNeeded = DWORD{ 0 };

      if (!QueryServiceConfig(
         srvHandle,
         nullptr,
         0,
         &bytesNeeded))
      {
         if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
         {
            std::vector<unsigned char> buffer(bytesNeeded, 0);

            auto lpsc = reinterpret_cast<LPQUERY_SERVICE_CONFIG>(buffer.data());
            if (QueryServiceConfig(
               srvHandle,
               lpsc,
               bytesNeeded,
               &bytesNeeded))
            {
               type = (ServiceType)lpsc->dwServiceType;
               startType = (ServiceStartType)lpsc->dwStartType;
               errorControl = (ServiceErrorControl)lpsc->dwErrorControl;
               pathName = lpsc->lpBinaryPathName;
               loadOrderGroup = lpsc->lpLoadOrderGroup;
               tagId = lpsc->dwTagId;
               dependencies = SplitDoubleNullTerminatedString(lpsc->lpDependencies);
               startName = lpsc->lpServiceStartName;
               displayName = lpsc->lpDisplayName;
            }
         }
      }

      bytesNeeded = 0;
      if (!QueryServiceConfig2(
         srvHandle,
         SERVICE_CONFIG_DESCRIPTION,
         nullptr,
         0,
         &bytesNeeded))
      {
         if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
         {
            std::vector<unsigned char> buffer(bytesNeeded, 0);

            if (QueryServiceConfig2(
               srvHandle,
               SERVICE_CONFIG_DESCRIPTION,
               reinterpret_cast<LPBYTE>(buffer.data()),
               bytesNeeded,
               &bytesNeeded))
            {
               auto lpsd = reinterpret_cast<LPSERVICE_DESCRIPTION>(buffer.data());

               description = lpsd->lpDescription;
            }
         }
      }
   }

private:
   static std::vector<ServiceString> SplitDoubleNullTerminatedString(LPCTSTR text)
   {
      std::vector<ServiceString> texts;
      LPCTSTR ptr = text;
      do 
      {
         texts.push_back(ptr);
         ptr += texts.back().size() + 1;
      } while (*ptr != _T('\0'));

      return texts;
   }
};