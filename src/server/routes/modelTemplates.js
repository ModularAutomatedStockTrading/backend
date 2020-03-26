const express = require("express");
const ModelTemplate = require("server/schema/modelTemplate").model;
const router = express.Router();

router.post("/", (req, res) => {
    const modelTemplate = new ModelTemplate(req.body.model);
    modelTemplate.save();
    res.send({modelTemplate : modelTemplate.toObject()});
});

router.get("/", async (req, res) => {
    const modelTemplates = await ModelTemplate.find();
    res.send({modelTemplates : modelTemplates.toObject()});
});

router.patch("/:id", async (req, res) => {
    const modelTemplate = await ModelTemplate.findByIdAndUpdate(req.params.id, req.body.data, {new : true});
    res.send({modelTemplate : modelTemplate.toObject()});
});

router.delete("/:id", async (req, res) => {
    await Model.findByIdAndDelete(req.params.id);
    res.sendStatus(200);
});

module.exports = router;