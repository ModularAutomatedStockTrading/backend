const express = require("express");
const ATE = require("src/server/schema/ATE").model;
const router = express.Router();

// handler for adding new ATE
router.post("/", (req, res) => {
    const ate = new ATE(req.body.data);
    ate.save();
    res.send({ATE : ate});
});

// handler for getting all ATEs
router.get("/", async (req, res) => {
    ATE.find().then(ATEs => {
        res.send({ATEs});
    });
});

// handler for changing an ATE by id
router.patch("/:id", async (req, res) => {
    ATE.findByIdAndUpdate(req.params.id, req.body.data, {new : true})
    .then((newATE) => {
        res.send({ATE : newATE});
    });
});

// handler for deleting ATE by id
router.delete("/:id", async (req, res) => {
    ATE.findByIdAndDelete(req.params.id)
    .then(() => {
        res.sendStatus(200);
    });
});

module.exports = router;