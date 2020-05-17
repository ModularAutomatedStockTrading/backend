const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

// schema for model
const struct = new Schema({
    ...require("./modelTemplate").struct,
    isTraining : Boolean,
    hasTrained : Boolean,
    weights : [[[Number]]],
    statistics : Object
});

// add to DB
module.exports.model = mongoose.model('Model', struct);