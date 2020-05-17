const dotenv = require('dotenv');
dotenv.config();

const express = require("express");
const bodyParser = require('body-parser');
const mongoose = require("mongoose");
const cors = require('cors')

// for debugging
let consoleCount = 0;
console.start = s => {
    consoleCount++;
    console.info("      ".repeat(consoleCount - 1), s);
}
console.stop = () => {
    consoleCount--;
}
console.log = (...args) => {
    if(consoleCount == 0) console.error("CONSOLE LOG NOT ALLOWED")
    else console.info("   ".repeat(consoleCount), ...args)
}

// debugging with docker
setInterval(() => {
    console.info("keeping stdout alive...")
}, 20000)

console.start("SETUP")

// routes
const modelRoutes = require("./routes/models");
const modelTemplateRoutes = require("./routes/modelTemplates");
const tradingRoutes = require("./routes/trading");
const ATERoutes = require("./routes/ATEs") 

// server
const app = express();

// middleware
app.use(cors());
app.use(express.json());

// setup routes
app.use("/models", modelRoutes);
app.use("/modelTemplates", modelTemplateRoutes);
app.use("/trading-api", tradingRoutes);
app.use("/ates", ATERoutes);

console.log("connecting to database...")

// connect to mongodb
mongoose.connect(`mongodb://${process.env.MONGODBURL}:27017/mtd`,
    {
        useNewUrlParser: true, useUnifiedTopology: true,
    }
);

mongoose.set('useFindAndModify', false);

// start server
app.listen(process.env.PORT, () => {
    console.log(`server running at ${process.env.PORT}...`)
    console.stop()
});
