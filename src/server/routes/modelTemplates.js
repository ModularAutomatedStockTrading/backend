const express = require("express");
const Model = require("server/schema/model").model;
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

router.patch("/:id", async (req, res) => {
    const model = await Model.findByIdAndUpdate(req.params.id, req.body.data, {new : true});
    res.send({model});
});

router.delete("/:id", async (req, res) => {
    await Model.findByIdAndDelete(req.params.id);
    res.sendStatus(200);
});

module.exports = router;