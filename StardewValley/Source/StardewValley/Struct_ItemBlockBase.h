#include "CoreMinimal.h"

/**
 *
 */
#include "Engine/DataTable.h"
#include "ItemBlockBase.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "Struct_ItemBlockBase.generated.h"

USTRUCT(BlueprintType)
struct FStruct_ItemBlockBase : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    FStruct_ItemBlockBase()
        : id_(0)
        , scale_(0.f)
        , name_(TEXT(""))
		, type_(0)
		, item_block_class_(nullptr)
		, mesh_(nullptr)
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    int32 id_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    float scale_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    FString name_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    int32 type_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	TMap<int32, int32> map_lifespan_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    TMap<int32, int32> map_item_drop_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    TArray<int32> interaction_accepted_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	TSubclassOf<AItemBlockBase> item_block_class_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    UStaticMesh* mesh_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    UMaterialInterface* material_;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
    int32 durability_;
};