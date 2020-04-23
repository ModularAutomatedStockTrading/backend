const express = require("express");
const ATE = require("src/server/schema/ATE").model;
const router = express.Router();

router.post("/", (req, res) => {
    const ate = new ATE(req.body.data);
    ate.save();
    res.send({ATE : ate});
});

router.get("/", async (req, res) => {
    ATE.find().then(ATEs => {
        res.send({ATEs});
    });
});

router.patch("/:id", async (req, res) => {
    ATE.findByIdAndUpdate(req.params.id, req.body.data, {new : true})
    .then((newATE) => {
        res.send({ATE : newATE});
    });
});

router.delete("/:id", async (req, res) => {
    ATE.findByIdAndDelete(req.params.id)
    .then(() => {
        res.sendStatus(200);
    });
});

module.exports = router;