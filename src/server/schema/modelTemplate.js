const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

// schema for model template
const input = new Schema({
    value : String,
    type : String,
    label : String
});

const output = new Schema({
    value : String,
    type : String,
    label : String
});

const struct = {
    name : String,
    description : String,
    amountOfHiddenLayers : Number,
    amountOfInputNodes : Number,
    amountOfOutputNodes : Number,
    amountOfHiddenLayerNodes : [Number],
    inputs : [input],
    outputs : [output]
};

module.exports.struct = struct;

// add to DB
module.exports.model = mongoose.model('ModelTemplate', new Schema(struct));