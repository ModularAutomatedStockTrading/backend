const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

const struct = new Schema({
    ...require("./modelTemplate").struct,
    isTraining : Boolean,
    hasTrained : Boolean,
    weights : [[[Number]]]
});

module.exports.model = mongoose.model('Model', struct);