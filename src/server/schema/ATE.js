const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

// schema for ATE
const ExtendedBoolean = {
    type : String,
    enum : ["false", "unset", "true"]
}

const struct = {
    name : String,
    description : String,
    modelID : mongoose.ObjectId,
    bidTrigger : [ExtendedBoolean],
    sellTrigger : [ExtendedBoolean]
};

// Adding to DB
module.exports.model = mongoose.model(
    'ATE',
    new Schema(struct)
);