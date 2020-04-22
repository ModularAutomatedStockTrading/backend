const dotenv = require('dotenv');
dotenv.config();

const express = require("express");
const bodyParser = require('body-parser');
const mongoose = require("mongoose");
const cors = require('cors')

const modelRoutes = require("./routes/models");
const modelTemplateRoutes = require("./routes/modelTemplates");
const tradingRoutes = require("./routes/trading");
const ATERoutes = require("./routes/ATEs")

const app = express();

app.use(cors());
app.use(express.json());

const port = 4000;

app.use("/models", modelRoutes);
app.use("/modelTemplates", modelTemplateRoutes);
app.use("/trading-api", tradingRoutes);
app.use("/ates", ATERoutes);

mongoose.connect('mongodb://localhost:27017/mtd', {useNewUrlParser: true, useUnifiedTopology: true });
mongoose.set('useFindAndModify', false);

app.listen(port, () => {
    console.log(`server running at port ${port}...`)
});