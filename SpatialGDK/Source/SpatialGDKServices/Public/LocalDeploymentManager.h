// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
#pragma once

#include "Async/Future.h"
#include "CoreMinimal.h"
#include "FileCache.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "TimerManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSpatialDeploymentManager, Log, All);

class FJsonObject;

class FLocalDeploymentManager
{
public:
	FLocalDeploymentManager();

	void SPATIALGDKSERVICES_API RefreshServiceStatus();

	bool SPATIALGDKSERVICES_API TryStartLocalDeployment(FString LaunchConfig, FString LaunchArgs);
	bool SPATIALGDKSERVICES_API TryStopLocalDeployment();

	bool SPATIALGDKSERVICES_API TryStartSpatialService();
	bool SPATIALGDKSERVICES_API TryStopSpatialService();

	bool SPATIALGDKSERVICES_API GetLocalDeploymentStatus();
	bool SPATIALGDKSERVICES_API GetServiceStatus();

	bool SPATIALGDKSERVICES_API IsLocalDeploymentRunning() const;
	bool SPATIALGDKSERVICES_API IsSpatialServiceRunning() const;

	bool SPATIALGDKSERVICES_API IsDeploymentStarting() const;
	bool SPATIALGDKSERVICES_API IsDeploymentStopping() const;

	bool SPATIALGDKSERVICES_API IsServiceStarting() const;
	bool SPATIALGDKSERVICES_API IsServiceStopping() const;

	void WorkerBuildConfigAsync();
	const FString GetSpotExe();

	FSimpleMulticastDelegate OnSpatialShutdown;
	FSimpleMulticastDelegate OnDeploymentStart;

	FDelegateHandle WorkerConfigDirectoryChangedDelegateHandle;
	IDirectoryWatcher::FDirectoryChanged WorkerConfigDirectoryChangedDelegate;

private:
	void StartUpWorkerConfigDirectoryWatcher();
	void OnWorkerConfigDirectoryChanged(const TArray<FFileChangeData>& FileChanges);
	bool IsServiceInCorrectDirectory(const FString& ServiceStatusResult);

	static const int32 ExitCodeSuccess = 0;

	// This is the frequency at which check the 'spatial service status' to ensure we have the correct state as the user can change spatial service outside of the editor.
	static const int32 RefreshFrequency = 3;

	bool bLocalDeploymentRunning;
	bool bSpatialServiceRunning;
	bool bSpatialServiceInProjectDirectory;

	bool bStartingDeployment;
	bool bStoppingDeployment;

	bool bStartingSpatialService;
	bool bStoppingSpatialService;

	FString LocalRunningDeploymentID;
};
