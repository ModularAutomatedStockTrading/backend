const mongoose = require("mongoose");
mongoose.set('useCreateIndex', true);
const Schema = require('mongoose').Schema;

const struct = new Schema({
    data : String,
    url : String,
    createdAt: {
        type: Date,
        default: Date.now
    }
});
struct.index({
    createdAt : 1
}, {expireAfterSeconds: 60})

const model = mongoose.model('ExternalCacheResponse', struct);;
model.on('index', function(error) {console.log("wdnjwndwjd")});

module.exports.ExternalCacheResponse = model;
