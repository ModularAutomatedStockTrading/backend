const mongoose = require("mongoose");

const Schema = require('mongoose').Schema;

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

module.exports.model = mongoose.model(
    'ATE',
    new Schema(struct)
);