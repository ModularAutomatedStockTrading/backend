const express = require("express");
const Instance = require("schema/instance").model;
const Model = require("schema/model").model;
const router = express.Router();

router.post("/", async (req, res) => {
    const modelID = req.body.data.modelID;
    const model = await Model.findById(modelID);
    delete model._id;
    const instance = new Instance({
        ...model.toObject(),
        name : req.body.data.name,
        description : req.body.data.description
    });
    instance.save();
    res.send({instance});
});

router.get("/", async (req, res) => {
    const instances = await Instance.find();
    res.send({instances});
});

router.patch("/:id", async (req, res) => {
    const instance = await Instance.findByIdAndUpdate(req.params.id, req.body.data, {new : true});
    res.send({instance});
});

router.delete("/:id", async (req, res) => {
    await Instance.findByIdAndDelete(req.params.id);
    res.sendStatus(200);
});

module.exports = router;