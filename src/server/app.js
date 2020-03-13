const express = require("express");
const bodyParser = require('body-parser');
const models = require("routes/models");
const mongoose = require("mongoose");
var cors = require('cors')

const app = express();

app.use(cors());
app.use(express.json());

const port = 4000;

app.use("/models", models);

mongoose.connect('mongodb://localhost:27017/modular_trading_database', {useNewUrlParser: true, useUnifiedTopology: true });

app.listen(port, () => {
    console.log(`server running at port ${port}...`)
});