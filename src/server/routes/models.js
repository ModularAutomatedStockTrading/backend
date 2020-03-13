const express = require("express");
const Model = require("schema/model");
const router = express.Router();

router.post("/", (req, res) => {
    const model = new Model(req.body.model);
    model.save();
    res.send({model});
});

router.get("/", async (req, res) => {
    const models = await Model.find();
    res.send({models});
});

router.patch("/:id", (req, res) => {
    res.send("hello patch");
});

module.exports = router;