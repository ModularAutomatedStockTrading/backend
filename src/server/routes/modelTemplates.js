const express = require("express");
const ModelTemplate = require("src/server/schema/modelTemplate").model;
const router = express.Router();

router.post("/", (req, res) => {
    const modelTemplate = new ModelTemplate(req.body.modelTemplate);
    modelTemplate.save();
    res.send({modelTemplate});
});

router.get("/", async (req, res) => {
    const modelTemplates = await ModelTemplate.find();
    res.send({modelTemplates});
});

router.patch("/:id", async (req, res) => {
    const modelTemplate = await ModelTemplate.findByIdAndUpdate(req.params.id, req.body.data, {new : true});
    res.send({modelTemplate});
});

router.delete("/:id", async (req, res) => {
    await ModelTemplate.findByIdAndDelete(req.params.id);
    res.sendStatus(200);
});

module.exports = router;