#pragma once 

#include "SquareObj.h"
#include "LineObj.h"
#include "AICar.h"
#include "Scene.h"

class Agent;

class SelfDrivingWorld : public Scene
{
public:
	std::vector<std::unique_ptr<AICar>> car_list_;
	std::vector<std::unique_ptr<Object>> obj_list;
	
protected:
	glm::mat4 View_;
	GLuint MatrixID_;
	glm::mat4 Projection_;

	network<sequential> nn_;
	int input_frame_cnt_;
	bool is_training_;

public:
	bool is_training() {return is_training_;}

	void initialize();
	void createAICars(int nums);

	// flag = 0 : continue, 1 : terminal
	void update(const bool& update_render_data, float& reward, int& flag);

	network<sequential>& getGlobalNetwork(){ return nn_; }
	const std::vector<std::unique_ptr<Object>>& getObjects() { return obj_list;}
	const std::vector<std::unique_ptr<AICar>>& getCars() { return car_list_; }

	void render();
	void run();

	static SelfDrivingWorld& get(){
		static SelfDrivingWorld main_scene;
		return main_scene;
	}

	bool handleKeyInput();

protected:
	SelfDrivingWorld();
	void createScene_RandomObstacles();
	void createScene_Basic();
};

// end of file
