const dotenv = require('dotenv');
dotenv.config();

const express = require("express");
const bodyParser = require('body-parser');
const models = require("./routes/models");
const instances = require("./routes/instances");
const mongoose = require("mongoose");
const cors = require('cors')
const trading = require("./routes/trading");

const app = express();

app.use(cors());
app.use(express.json());

const port = 4000;

app.use("/models", models);
app.use("/instances", instances);
app.use("/api", trading);

mongoose.connect('mongodb://localhost:27017/mtd', {useNewUrlParser: true, useUnifiedTopology: true });
mongoose.set('useFindAndModify', false);

app.listen(port, () => {
    console.log(`server running at port ${port}...`)
});