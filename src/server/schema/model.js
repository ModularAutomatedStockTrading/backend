const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

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

const schema = new Schema({
    name : String,
    description : String,
    amountOfHiddenLayers : Number,
    amountOfInputNodes : Number,
    amountOfOutputNodes : Number,
    amountOfHiddenLayerNodes : [Number],
    inputs : [input],
    outputs : [output]
});

module.exports = mongoose.model('Model', schema);