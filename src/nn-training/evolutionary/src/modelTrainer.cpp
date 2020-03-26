#include "modelTrainer.h"

ModelTrainer::ModelTrainer(int layer_cnt, int* model, std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& output) {
    ModelTrainer::training_data_input = input;
    ModelTrainer::training_data_output = output;
}

ModelTrainer::getInputSize() {
    return ModelTrainer::training_data_input.size();
}
