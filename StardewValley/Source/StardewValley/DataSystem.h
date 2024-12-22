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
#include "ItemBlockBase.h"
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
	//Item block data
	TArray<AItemBlockBase*> item_blocks_;
	TArray<int32> item_block_id_;
	TArray<int32> item_block_lived_time_;
	TArray<int32> item_block_durability_;
	TArray<bool> is_item_block_watered_;
	bool is_items_initialized_;
private:
	//Time data
	int32 present_season_;
	int32 day_in_season_;
	int32 hour_;
	int32 minute_;
	int32 real_time_;
private:
	//Weather data
	int32 present_weather_;
	int32 present_base_temperature_;
private:
	//Player data
	int32 player_axe_level_;
	int32 player_hoe_level_;
	int32 player_scythe_level_;
	int32 player_axe_exp_;
	int32 player_hoe_exp_;
	int32 player_scythe_exp_;
	TMap<int32, int32> player_bag_;
public:
	//shortCutBar id
	TArray <int32> shortBar_;
	/*-----------------------------Getters-----------------------------*/
public:
	//Time data getters
	int32 get_present_season() { return present_season_; };
	int32 get_day_in_season() { return day_in_season_; };
	int32 get_hour() { return hour_; };
	int32 get_minute() { return minute_; };
	int32 get_real_time() { return real_time_; };
public:
	//Ground block data getters
	int32 get_ground_block_size() { return ground_block_size_; };
	int32 get_ground_block_x_length() { return ground_block_x_length_; };
	int32 get_ground_block_y_length() { return ground_block_y_length_; };
	FString get_ground_block_type(int32 index) { if (index < ground_block_type_.Num() && index >= 0)return ground_block_type_[index]; else return ""; };
	FString get_ground_block_type(int32 x, int32 y) { if (x * ground_block_y_length_ + y < ground_block_type_.Num() && x * ground_block_y_length_ + y >= 0)return ground_block_type_[x * ground_block_y_length_ + y]; else return ""; };
	int32 get_ground_block_delta_temperature(int32 index) { if (index < ground_block_delta_temperature_.Num() && index >= 0)return ground_block_delta_temperature_[index]; else return 0; };
	int32 get_ground_block_delta_temperature(int32 x, int32 y) { if (x * ground_block_y_length_ + y < ground_block_delta_temperature_.Num() && x * ground_block_y_length_ + y >= 0)return ground_block_delta_temperature_[x * ground_block_y_length_ + y]; else return 0; };
	AGroundBlockBase* get_ground_block(int32 index) { if (index < ground_blocks_.Num() && index >= 0)return ground_blocks_[index]; else return nullptr; };
	AGroundBlockBase* get_ground_block(int32 x, int32 y) { if (x * ground_block_y_length_ + y < ground_blocks_.Num() && x * ground_block_y_length_ + y >= 0)return ground_blocks_[x * ground_block_y_length_ + y]; else return nullptr; };
public:
	//Item block data getters
	AItemBlockBase* get_item_block(int32 index) { if (index < item_blocks_.Num() && index >= 0)return item_blocks_[index]; else return nullptr; };
	AItemBlockBase* get_item_block(int32 x, int32 y) { if (x * ground_block_y_length_ + y < item_blocks_.Num() && x * ground_block_y_length_ + y >= 0)return item_blocks_[x * ground_block_y_length_ + y]; else return nullptr; };
	int32 get_item_block_id(int32 index) { if (index < item_block_id_.Num() && index >= 0)return item_block_id_[index]; else return -1; };
	int32 get_item_block_id(int32 x, int32 y) { if (x * ground_block_y_length_ + y < item_block_id_.Num() && x * ground_block_y_length_ + y >= 0)return item_block_id_[x * ground_block_y_length_ + y]; else return -1; };
	int32 get_item_block_lived_time(int32 index) { if (index < item_block_lived_time_.Num() && index >= 0)return item_block_lived_time_[index]; else return -1; };
	int32 get_item_block_lived_time(int32 x, int32 y) { if (x * ground_block_y_length_ + y < item_block_lived_time_.Num() && x * ground_block_y_length_ + y >= 0)return item_block_lived_time_[x * ground_block_y_length_ + y]; else return -1; };
	int32 get_item_block_durability(int32 index) { if (index < item_block_durability_.Num() && index >= 0)return item_block_durability_[index]; else return -1; };
	int32 get_item_block_durability(int32 x, int32 y) { if (x * ground_block_y_length_ + y < item_block_durability_.Num() && x * ground_block_y_length_ + y >= 0)return item_block_durability_[x * ground_block_y_length_ + y]; else return -1; };
	bool get_is_item_block_watered(int32 index) { if (index < is_item_block_watered_.Num() && index >= 0)return is_item_block_watered_[index]; else return false; };
	bool get_is_item_block_watered(int32 x, int32 y) { if (x * ground_block_y_length_ + y < is_item_block_watered_.Num() && x * ground_block_y_length_ + y >= 0)return is_item_block_watered_[x * ground_block_y_length_ + y]; else return false; };
	bool is_items_initialized() { return is_items_initialized_; };
public:
	//Weather data getters
	int32 get_present_weather() { return present_weather_; };
	int32 get_present_base_temperature() { return present_base_temperature_; };
public:
	//Player data getters
	int32 get_player_axe_level() { return player_axe_level_; };
	int32 get_player_hoe_level() { return player_hoe_level_; };
	int32 get_player_scythe_level() { return player_scythe_level_; };
	int32 get_player_axe_exp() { return player_axe_exp_; };
	int32 get_player_hoe_exp() { return player_hoe_exp_; };
	int32 get_player_scythe_exp() { return player_scythe_exp_; };
	int32 get_amount_of_item_in_bag(int32 index) { if (player_bag_.Contains(index))return player_bag_[index]; else return 0; };
	TMap<int32, int32> get_player_bag() { return player_bag_; };
	int32 getShortBar(int32 index) {
		if (index < 1 || index > 10) return 0;
		while (index + 1 >= shortBar_.Num()) shortBar_.Add(0);
		return shortBar_[index];
	};
	TArray<int32> getShortBar() { return shortBar_; };
	/*-----------------------------Setters-----------------------------*/
public:
	//Time data setters
	void set_present_season(int32 season) { present_season_ = season; };
	void set_day_in_season(int32 day) { day_in_season_ = day; };
	void set_hour(int32 hour) { hour_ = hour; };
	void set_minute(int32 minute) { minute_ = minute; };
	void set_real_time(int32 time) { real_time_ = time; };
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
public:
	//Item block data setters
	void set_item_block(int32 index, AItemBlockBase* block) { while (item_blocks_.Num() <= index) { item_blocks_.Add(nullptr); }; item_blocks_[index] = block; };
	void set_item_block(int32 x, int32 y, AItemBlockBase* block) { set_item_block(x * ground_block_y_length_ + y, block); };
	void set_item_block_id(int32 index, int32 id) { while (item_block_id_.Num() <= index) { item_block_id_.Add(-1); }; item_block_id_[index] = id; };
	void set_item_block_id(int32 x, int32 y, int32 id) { set_item_block_id(x * ground_block_y_length_ + y, id); };
	void set_item_block_lived_time(int32 index, int32 status) { while (item_block_lived_time_.Num() <= index) { item_block_lived_time_.Add(-1); }; item_block_lived_time_[index] = status; };
	void set_item_block_lived_time(int32 x, int32 y, int32 status) { set_item_block_lived_time(x * ground_block_y_length_ + y, status); };
	void set_item_block_durability(int32 index, int32 durability) { while (item_block_durability_.Num() <= index) { item_block_durability_.Add(-1); }; item_block_durability_[index] = durability; };
	void set_item_block_durability(int32 x, int32 y, int32 durability) { set_item_block_durability(x * ground_block_y_length_ + y, durability); };
	void set_is_item_block_watered(int32 index, bool is_watered) { while (is_item_block_watered_.Num() <= index) { is_item_block_watered_.Add(false); }; is_item_block_watered_[index] = is_watered; };
	void set_is_item_block_watered(int32 x, int32 y, bool is_watered) { set_is_item_block_watered(x * ground_block_y_length_ + y, is_watered); };
	void set_is_items_initialized(bool is_initialized) { is_items_initialized_ = is_initialized; };
public:
	//Player data setters
	void set_player_axe_level(int32 level) { player_axe_level_ = level; };
	void set_player_hoe_level(int32 level) { player_hoe_level_ = level; };
	void set_player_scythe_level(int32 level) { player_scythe_level_ = level; };
	void set_player_axe_exp(int32 exp) { player_axe_exp_ = exp; };
	void set_player_hoe_exp(int32 exp) { player_hoe_exp_ = exp; };
	void set_player_scythe_exp(int32 exp) { player_scythe_exp_ = exp; };
	void add_item_to_bag(int32 id, int32 amount) {
		if (player_bag_.Contains(id)) { player_bag_[id] += amount; }
		else { player_bag_.Add(id, amount); };
	}
	void set_shortBar(TArray<int32> shortCutBar) { shortBar_ = shortCutBar; };
	void set_shortBar(int32 index, int32 id) { if (index < 1 || index > 10) return; while (shortBar_.Num() <= index) { shortBar_.Add(0); }; shortBar_[index] = id; };
	/*-----------------------------Others-----------------------------*/
public:
	//Other functions
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;
	/**
	 * Saves the game.
	 *
	 */
	void SaveGame();
	/**
	 * Loads the game.
	 *
	 */
	void LoadGame();
	bool do_save;
};
