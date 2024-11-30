/****************************************************************
 * \file   DataSystem.h
 * \brief  Data system is a system to store all the data necessary.
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GroundBlockBase.h"
#include "DataSystem.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UDataSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	/*-----------------------------Variables-----------------------------*/
private:
	//Ground block data
	int32 ground_block_x_length_;
	int32 ground_block_y_length_;
	int32 ground_block_size_;
	TArray<AGroundBlockBase*> ground_blocks_;
	TArray<FString> ground_block_type_;
	TArray<int32> ground_block_delta_temperature_;
private:
	//Time data
	int32 present_season_;
	int32 day_in_season_;
	int32 hour_;
	int32 minute_;
private:
	//Weather data
	int32 present_weather_;
	int32 present_base_temperature_;

	/*-----------------------------Getters-----------------------------*/
public:
	//Time data getters
	int32 get_present_season() { return present_season_; };
	int32 get_day_in_season() { return day_in_season_; };
	int32 get_hour() { return hour_; };
	int32 get_minute() { return minute_; };
public:
	//Ground block data getters
	int32 get_ground_block_size() { return ground_block_size_; };
	int32 get_ground_block_x_length() { return ground_block_x_length_; };
	int32 get_ground_block_y_length() { return ground_block_y_length_; };
	FString get_ground_block_type(int32 index) { if(index < ground_block_type_.Num() && index >= 0)return ground_block_type_[index];else return ""; };
	FString get_ground_block_type(int32 x, int32 y) { if(x * ground_block_y_length_ + y < ground_block_type_.Num() && x * ground_block_y_length_ + y >= 0)return ground_block_type_[x * ground_block_y_length_ + y];else return ""; };
	int32 get_ground_block_delta_temperature(int32 index) { if(index < ground_block_delta_temperature_.Num() && index >= 0)return ground_block_delta_temperature_[index];else return 0; };
	int32 get_ground_block_delta_temperature(int32 x, int32 y) { if(x * ground_block_y_length_ + y < ground_block_delta_temperature_.Num() && x * ground_block_y_length_ + y >= 0)return ground_block_delta_temperature_[x * ground_block_y_length_ + y];else return 0; };
	AGroundBlockBase* get_ground_block(int32 index) { if (index < ground_blocks_.Num() && index >= 0)return ground_blocks_[index]; else return nullptr; };
	AGroundBlockBase* get_ground_block(int32 x, int32 y) { if (x * ground_block_y_length_ + y < ground_blocks_.Num() && x * ground_block_y_length_ + y >= 0)return ground_blocks_[x * ground_block_y_length_ + y]; else return nullptr; };

public:
	//Weather data getters
	int32 get_present_weather() { return present_weather_; };
	int32 get_present_base_temprature() { return present_base_temperature_; };

	/*-----------------------------Setters-----------------------------*/
public:
	//Time data setters
	void set_present_season(int32 season) { present_season_ = season; };
	void set_day_in_season(int32 day) { day_in_season_ = day; };
	void set_hour(int32 hour) { hour_ = hour; };
	void set_minute(int32 minute) { minute_ = minute; };
public:
	//Weather data setters
	void set_present_weather(int32 weather) { present_weather_ = weather; };
	void set_present_base_temperature(int32 temperature) { present_base_temperature_ = temperature; };
public:
	//Ground block data setters
	void set_ground_block_size(int32 size) { ground_block_size_ = size; };
	void set_ground_block_x_length(int32 length) { ground_block_x_length_ = length; };
	void set_ground_block_y_length(int32 length) { ground_block_y_length_ = length; };
	void set_ground_block_type(int32 index, FString type) { while (ground_block_type_.Num() <= index) { ground_block_type_.Add(""); }; ground_block_type_[index] = type; };
	void set_ground_block_type(int32 x, int32 y, FString type) { set_ground_block_type(x * ground_block_y_length_ + y, type); };
	void set_ground_block_delta_temperature(int32 index, int32 delta_temperature) { while (ground_block_delta_temperature_.Num() <= index) { ground_block_delta_temperature_.Add(0); }; ground_block_delta_temperature_[index] = delta_temperature; };
	void set_ground_block_delta_temperature(int32 x, int32 y, int32 delta_temperature) { set_ground_block_delta_temperature(x * ground_block_y_length_ + y, delta_temperature); };
	void set_ground_block(int32 index, AGroundBlockBase* block) { while (ground_blocks_.Num() <= index) { ground_blocks_.Add(nullptr); }; ground_blocks_[index] = block; };
	void set_ground_block(int32 x, int32 y, AGroundBlockBase* block) { set_ground_block(x * ground_block_y_length_ + y, block); };

	/*-----------------------------Others-----------------------------*/
public:
	//Other functions
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;
};
