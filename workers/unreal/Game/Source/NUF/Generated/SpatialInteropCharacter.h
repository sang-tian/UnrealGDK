#include "GameFramework/Actor.h"
#include "UnrealACharacterReplicatedDataComponent.h"

class USpatialPackageMapClient;

TMap<int, TPair<UProperty*, UProperty*>> CreateCmdIndexToPropertyMap_Character();

void ApplyUpdateToSpatial_Character(AActor* Actor, int CmdIndex, UProperty* ParentProperty, UProperty* Property, UUnrealACharacterReplicatedDataComponent* ReplicatedData, USpatialPackageMapClient* PackageMap);

void ReceiveUpdateFromSpatial_Character(AActor* Actor, TMap<int, TPair<UProperty*, UProperty*>>& CmdIndexToPropertyMap, UUnrealACharacterReplicatedDataComponentUpdate* Update);
