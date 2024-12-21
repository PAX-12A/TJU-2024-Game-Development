// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"  // 包含 UObject 及其派生类相关的功能
/**

 * */
//USTRUCT(BlueprintType)
//struct FMarketItem
//{
//    GENERATED_USTRUCT_BODY()
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
//    FString ItemName;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
//    int32 ItemPrice;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
//    int32 ItemStock;
//
//    FMarketItem()
//        : ItemName(TEXT("Unknown")), ItemPrice(0), ItemStock(0)
//    {}
//};
//UCLASS()
//class STARDEWVALLEY_API UMarket : public UObject
//{
//    GENERATED_BODY()
//
//public:
//    UMarket();
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
//    TArray<FMarketItem> MarketItems;
//
//    UFUNCTION(BlueprintCallable, Category = "Market")
//    bool BuyItem(int32 ItemIndex, int32& PlayerMoney);
//
//    UFUNCTION(BlueprintCallable, Category = "Market")
//    bool SellItem(int32 ItemIndex, int32& PlayerMoney);
//
//};
//
//UMarket::UMarket()
//{
//    // 初始化 MarketItems 或进行其他初始化
//    MarketItems = TArray<FMarketItem>();
//}
//
//bool UMarket::BuyItem(int32 ItemIndex, int32& PlayerMoney)
//{
//    if (ItemIndex >= 0 && ItemIndex < MarketItems.Num())
//    {
//        FMarketItem& Item = MarketItems[ItemIndex];
//        if (PlayerMoney >= Item.ItemPrice && Item.ItemStock > 0)
//        {
//            PlayerMoney -= Item.ItemPrice;
//            Item.ItemStock--;
//            return true;
//        }
//    }
//    return false;
//}
//
//bool UMarket::SellItem(int32 ItemIndex, int32& PlayerMoney)
//{
//    if (ItemIndex >= 0 && ItemIndex < MarketItems.Num())
//    {
//        FMarketItem& Item = MarketItems[ItemIndex];
//        Item.ItemStock++;
//        PlayerMoney += Item.ItemPrice;
//        return true;
//    }
//    return false;
//}