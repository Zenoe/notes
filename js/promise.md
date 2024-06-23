## async function return undefined if it does not explicitly return a promise

The code you've provided does not explicitly return a promise. Instead, it appears to use a callback-based approach to handle asynchronous operations. In this case, the batchAdd function itself does not return a promise directly.
When an asynchronous function does not explicitly return a promise, it typically returns undefined by default. 

const batchAdd = async (Model, req, res) => {
  return upload.single("file")(req, res, async (err) => {
    if (err instanceof multer.MulterError) {
      // A Multer error occurred (e.g., file size limit exceeded)
      return res.status(400).json({ error: err.message });
    } else if (err) {
      logger.error(err);
      return res.status(500).json({ error: "Internal Server Error" });
    }

    if (!req.file) {
      return res.status(400).json({ error: "No file uploaded." });
    }

    await Model.insertMany(jsonArray);
    res.json({
      success: true,
      result: null,
      message: "batch add completed",
    });
  });
}


## wrap the callback-based function to a promise-based function
In the provided code, the `batchAdd` function is an asynchronous function that uses `upload.single("file")` to handle file uploads. However, the use of `upload.single("file")` with an async callback makes it challenging to directly convert this code to return a promise.
To handle this scenario, you can wrap the logic inside a promise and use the `util.promisify` method to convert the callback-based function to a promise-based function. 

```javascript
const util = require('util');
const uploadPromise = util.promisify(upload.single("file"));

const batchAdd = async (Model, req, res) => {
  try {
    await uploadPromise(req, res);
    if (!req.file) {
      return res.status(400).json({ error: "No file uploaded." });
    }
    await Model.insertMany(jsonArray);
    res.json({
      success: true,
      result: null,
      message: "batch add completed",
    });
  } catch (err) {
    if (err instanceof multer.MulterError) {
      // A Multer error occurred (e.g., file size limit exceeded)
      return res.status(400).json({ error: err.message });
    } else {
      logger.error(err);
      return res.status(500).json({ error: "Internal Server Error" });
    }
  }
};
```

- Inside the `batchAdd` function, `await uploadPromise(req, res)` is used to asynchronously handle the file upload operation using the promise-based function.

By using `util.promisify` and restructuring the error handling, the `batchAdd` function now returns a promise and handles the asynchronous file upload and database insertion operations. This allows you to use `batchAdd` as an asynchronous function and handle its outcome using `try/catch` and `await`.
