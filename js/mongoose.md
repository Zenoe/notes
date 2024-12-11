## const result = await MyModel.find().select('field1 field2 -field3');
## YourModel.find({ a: 1, b: { $ne: 2 } })
## `findOne vs findOne .exec()`
using `.exec()` allows you to chain additional query methods to modify the query before execution.

   ```javascript
   const resultPromise = MyModel.findOne({ name: 'John' });
   
   resultPromise.then((doc) => {
     console.log(doc);
   }).catch((error) => {
     console.error(error);
   });
   ```

   In this case, `resultPromise` is a promise object that represents the asynchronous operation of finding a document. You can use `.then()` to handle the successful case and `.catch()` to handle any errors that occur during the query.

   ```javascript
   const resultPromise = MyModel.findOne({ name: 'John' }).select('name').exec();
   resultPromise.then((doc) => {
     console.log(doc);
   }).catch((error) => {
     console.error(error);
   });
   ```

## `autopopulate`
The line `schema.plugin(require('mongoose-autopopulate'));` is using the `mongoose-autopopulate` plugin in a Mongoose schema.
automatically populates referenced fields in a MongoDB document when querying or retrieving data. 
To use the `mongoose-autopopulate` plugin, you need to have the `mongoose` package installed. Once you have it installed, you can require the plugin and apply it to your Mongoose schema using the `schema.plugin()` method.
Here's an example of how you can use `mongoose-autopopulate` in a Mongoose schema:

```javascript
const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const autopopulate = require('mongoose-autopopulate');

const userSchema = new Schema({
  name: String,
  posts: [{
    type: Schema.Types.ObjectId,
    ref: 'Post',
    autopopulate: true // Enable autopopulation for the 'posts' field
  }]
});

userSchema.plugin(autopopulate);

const User = mongoose.model('User', userSchema);
```

 the plugin is applied to the `userSchema` using `userSchema.plugin(autopopulate)`. This enables the autopopulation feature for the `posts` field in the `User` schema.

By applying the `mongoose-autopopulate` plugin, you don't need to manually populate the `posts` field whenever you retrieve a `User` document. The plugin will automatically populate the `posts` field with the corresponding `Post` documents based on the references defined in the schema.

When I mentioned "manually populating the `posts` field," I was referring to the process of explicitly populating the referenced field with the corresponding documents.

In Mongoose, when you have a field that references another collection (like the `posts` field in the example schema), the referenced field initially contains only the ObjectId(s) of the referenced document(s). To retrieve the actual document(s) being referenced, you need to perform a separate query and populate the field with the referenced document(s).

Without using a plugin like `mongoose-autopopulate`, you would need to explicitly call the `populate()` method on the Mongoose query to populate the `posts` field. Here's an example:

```javascript
const User = mongoose.model('User', userSchema);

User.findOne({ name: 'John' })
  .populate('posts') // Manually populate the 'posts' field
  .exec((err, user) => {
    if (err) {
      // Handle error
    } else {
      console.log(user.posts); // Access the populated 'posts' field
    }
  });
```

In the code above, the `populate()` method is called on the Mongoose query to populate the `posts` field. This triggers a separate query to retrieve the referenced `Post` documents and populates the `posts` field with the actual documents.

However, by using the `mongoose-autopopulate` plugin, you can automate this population process. The plugin handles the population automatically for you, eliminating the need for manual population calls. This simplifies your code and reduces the need for additional queries to retrieve the referenced documents.

With `mongoose-autopopulate` enabled in the schema, the `posts` field will be automatically populated whenever you retrieve a `User` document. You don't have to explicitly call `populate()` on the query or handle the population manually.

*****
In Mongoose, the `populate` method is used to automatically populate referenced documents from other collections when executing a query. It allows you to retrieve related data by referencing documents from other collections using references or object IDs.

Let's say you have two Mongoose models: `User` and `Post`. Each `Post` document has a reference to a `User` document through a field called `author`. By using `populate`, you can automatically retrieve the corresponding `User` document when querying for `Post` documents.

Here's an example to illustrate how to use `populate`:

```javascript
const mongoose = require('mongoose');

// Define the User schema
const userSchema = new mongoose.Schema({
  name: String,
  age: Number,
});

// Define the Post schema
const postSchema = new mongoose.Schema({
  title: String,
  content: String,
  author: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User', // Reference to the User model
  },
});

// Create the User and Post models
const User = mongoose.model('User', userSchema);
const Post = mongoose.model('Post', postSchema);

// Query for posts and populate the 'author' field
Post.find().populate('author').exec((error, posts) => {
  if (error) {
    console.error(error);
  } else {
    console.log(posts);
  }
});
```

In this example, we define the `User` and `Post` schemas using `mongoose.Schema`. The `author` field in the `postSchema` references the `User` model by specifying its object ID type and using the `ref` option to indicate the referenced model.

To populate the `author` field when querying for `Post` documents, we chain the `populate('author')` method to the query. This instructs Mongoose to fetch the referenced `User` document and replace the `author` field with the corresponding document.

Finally, we call `exec()` to execute the query and handle the result. The result will contain the `Post` documents with the `author` field populated with the corresponding `User` documents.

The `populate` method is a powerful feature in Mongoose that simplifies working with related data by automatically populating referenced documents. It helps avoid manual querying and referencing when retrieving related data, making it easier to work with complex data relationships.

## create vs save
create is typically used for creating new documents, especially in bulk, while save is used for updating existing documents or when you need more control over the save operation at the document level.

const User = mongoose.model('User', userSchema);
User.create({ name: 'Alice', age: 30 })
    .then(user => {
        console.log(user);
    })
    .catch(error => {
        console.error(error);
    });
////////////////////
const user = new User({ name: 'Bob', age: 25 });
user.save()
    .then(savedUser => {
        console.log(savedUser);
    })
    .catch(error => {
        console.error(error);
    });
const User = require('./models/User');

// Find the user by name
User.findOne({ name: 'Alice' })
  .then((user) => {
    if (!user) {
      console.log('User not found');
      return;
    }

    // Update the age of the user
    user.age = 35;

    // Save the updated user
    return user.save();
  })
  .then((updatedUser) => {
    if (updatedUser) {
      console.log('User updated successfully:', updatedUser);
    }
  })
  .catch((error) => {
    console.error('Error updating user:', error);
  });

## store file
In MongoDB, when dealing with storing associated text files, you have several options to consider. Here are some common approaches:

1. **GridFS**: MongoDB provides a specification called GridFS for storing and retrieving large files, such as text documents, images, videos, etc. GridFS stores files in two collections: `files` and `chunks`. This approach is suitable for handling large files that exceed the BSON document size limit of 16 MB.

2. **File References**: Instead of storing the actual text content in the database, you can store references to the text files. This can be achieved by storing file paths, URLs, or unique identifiers that point to the external location where the text files are stored.

3. **Binary Data**: If the text files are relatively small and won't exceed the BSON document size limit, you can store the text content directly within MongoDB documents as binary data using the `BinData` type. However, this approach may not be efficient for large files or a large number of files.

4. **Hybrid Approach**: You can combine different approaches based on the size and nature of the text files. For example, store smaller text files directly in MongoDB documents as binary data and use GridFS for larger files.

When deciding on the best approach for storing text files in MongoDB, consider factors such as file size, frequency of access, performance requirements, scalability, and the overall data model of your application. GridFS is a recommended approach for handling large files efficiently in MongoDB, while storing references or identifiers to external storage can be suitable for managing a large number of files without increasing the database size significantly.

## getIndexes
In the MongoDB shell, you can use the `getIndexes()` method to show the indexes for a specific collection
1. Open the MongoDB shell and switch to your desired database using the `use` command:

```javascript
use your_database_name
```

Replace `your_database_name` with the name of your database.

2. Once you are in the correct database, you can run the following command to show the indexes for a specific collection:

```javascript
db.your_collection_name.getIndexes()
```

Replace `your_collection_name` with the name of your collection.

When you run this command, MongoDB will return a list of all the indexes on the specified collection, including the default index on the `_id` field.

Here's an example of the output you might see:

```javascript
{
  "v" : 2,
  "key" : {
    "_id" : 1
  },
  "name" : "_id_",
  "ns" : "your_database_name.your_collection_name"
}
```

This output shows the default index on the `_id` field. If you have additional indexes, they will be listed as well.

This is how you can view the indexes for a collection using the MongoDB shell.

 mongoose defined filed with uinque to be true, it will automatically create index for you, but not immediately
 in the output of getIndexes(), you will see 
 ```javascript
 "background" : true
 ```
 which indicate that the index named "your_index_name" was created in the background.
 the index creation process has been initiated in the background. However, it does not necessarily mean that the index creation has been completed at the time when you retrieved the index information.

## index
The `index: true` property in Mongoose is used for creating a standard index on a field, which is different from a unique index. Here are a few reasons why you might still want to use `index: true`:

1. **Non-Unique Indexes**: If you want to improve the performance of query operations on a field that does not require uniqueness, you would use `index: true` without `unique: true`. This is because indexing a field can significantly speed up find operations and other read operations that use the indexed field.

2. **Compound Indexes**: If you're creating compound indexes (indexes on multiple fields), you might use `index: true` in combination with the `index` method on the schema to define the compound index.

3. **Special Index Types**: MongoDB supports various special index types like text indexes, geospatial indexes, etc. For these, you might use `index: { 'text': true }` or another similar syntax to create the special index.

4. **Control Over Index Creation**: Sometimes, developers want to have control over when and how indexes are created, especially in production environments where creating indexes can impact performance. In such cases, they might define indexes in the schema but create them manually at a more opportune time.

5. **Clarity and Explicitness**: Some developers prefer to explicitly state `index: true` for clarity, even if it's not necessary with `unique: true`, to make it clear to anyone reading the code that the field is indeed indexed.

Here's an example of using `index: true` for a non-unique index:

```javascript
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const yourSchema = new Schema({
  aField: {
    type: String,
    index: true, // This field should be indexed to improve query performance
  },
  anotherField: {
    type: Number,
    unique: true, // This field should be unique and will be automatically indexed
  },
  // Other fields and indexes
});

const YourModel = mongoose.model('YourModel', yourSchema);

module.exports = YourModel;
```

In the example above, `aField` will have a standard index, while `anotherField` will have a unique index. This demonstrates a scenario where you might want to use `index: true` independently of `unique: true`.

## 
```javascript
$project:{
    uniqueBugSet: {
      $filter: {
        input: "$uniqueBugSet",
        as: "bugIds",
        cond: { $ne: ["$$bugIds", 0] }, // Corrected to use $bugIds
      },
    },
    bugCount: { $size: "$uniqueBugSet" },
}
```
There's a misunderstanding in your approach to dynamically calculate `bugCount` based on the filtered `uniqueBugSet`. The issue is that the `$size` operator is applied to the original `uniqueBugSet` array before it's filtered, not to the result of the `$filter` operation. To achieve your goal, you need to ensure that `bugCount` is calculated after the `uniqueBugSet` array has been filtered.

Unfortunately, MongoDB's aggregation framework doesn't allow direct referencing of newly computed fields within the same `$project` or `$addFields` stage. To work around this limitation, you can use a two-step process. Here's how you can adjust your aggregation pipeline:

```javascript
db.collection.aggregate([
  {
    $addFields: {
      uniqueBugSet: {
        $filter: {
          input: "$uniqueBugSet",
          as: "bugIds",
          cond: { $ne: ["$$bugIds", 0] }
        }
      }
    }
  },
  {
    $addFields: {
      bugCount: { $size: "$uniqueBugSet" }
    }
  }
  // ...possibly more stages...
]);
```

In this corrected version, the pipeline first filters `uniqueBugSet` to exclude elements with the value `0`, using the `$addFields` stage to overwrite the original `uniqueBugSet` with the filtered results. Then, in a subsequent `$addFields` stage, it calculates `bugCount` based on the now filtered `uniqueBugSet`.

This approach ensures that `bugCount` reflects the size of `uniqueBugSet` after it has been filtered, accurately counting the number of elements that are not `0`.

#### combine project with addFields
```javascript
    {
      $project: {
        deviceModelName: "$_id",
        uniqueBugSet: {
          $filter: {
            input: "$uniqueBugSet",
            as: "bugIds",
            cond: { $ne: ["$$bugIds", 0] },
          },
        },
        }
    }
    {
      $addFields: {
        bugCount: { $size: "$uniqueBugSet" },
      },
    },

```

## console.log( { ...result }, result);   got
mongoose founded result is not ordinary js object
{
  '$__': InternalCache {
    activePaths: StateMachine { paths: [Object], states: [Object] },
    skipId: true,
    populated: { children: [Object] }
  },
  '$isNew': false,
  _doc: {
    _id: 'Do1YQVwtA5AFM2ZbEnlRV',
    name: 'dafasdf',
    children: [ [Object] ],
    __v: 0
  },
  businessId: 141,
  visibility: 'private'
}

 {
  _id: 'Do1YQVwtA5AFM2ZbEnlRV',
  name: 'dafasdf',
  children: [
    {...
    },
  ],
  __v: 0
}
It seems like the `result` object you're logging contains additional Mongoose-related metadata (`$__`, `$isNew`, etc.) along with the actual document data under `_doc`. This happens because `result` is still a Mongoose document object, and Mongoose attaches its internal state to it.

To get a clean version of the document data without Mongoose's metadata, you can either convert the Mongoose document to a plain JavaScript object using `.toObject()` or `.lean()` in the query. Here's how you can modify the code:

### Option 1: Use `.toObject()`
```javascript
if (result) {
  // Safely assign businessId and visibility if searchResult[0] exists
  if (searchResult.length > 0) {
    result.businessId = searchResult[0].businessId;
    result.visibility = searchResult[0].visibility;
  } else {
    console.log("No metadata found for this tree.");
  }

  // Convert Mongoose document to a plain JavaScript object
  const plainResult = result.toObject();

  console.log("result.visibility = ", result.visibility, plainResult);

  return res.status(200).json({
    success: true,
    result: plainResult,
    message: "Document found with id: " + req.params.id,
  });
}
```

### Option 2: Use `.lean()` in the Query
If you don't need Mongoose's document methods (like `.save()` or `.validate()`), you can use `.lean()` to get plain JavaScript objects directly from the query:

```javascript
const result = await getTreeWithDepth(Model, req.params.id).lean();

if (result) {
  // Safely assign businessId and visibility if searchResult[0] exists
  if (searchResult.length > 0) {
    result.businessId = searchResult[0].businessId;
    result.visibility = searchResult[0].visibility;
  } else {
    console.log("No metadata found for this tree.");
  }

  console.log("result.visibility = ", result.visibility, result);

  return res.status(200).json({
    success: true,
    result,
    message: "Document found with id: " + req.params.id,
  });
}
```

### Summary
- **`toObject()`**: Converts a Mongoose document to a plain JavaScript object.
- **`lean()`**: Directly returns a plain JavaScript object from the query without any Mongoose document metadata. 

In both cases, you'll get a clean object in `result` without the Mongoose internal properties like `"$__"`, `"isNew"`, etc.


### Nmts
db.getCollection("atsprojects").getIndexes()
db.getCollection("atsprojects").dropIndex("projectName_1")

> db.fixedtestbeds.createIndex({testBedName: 1}, {unique:true})
{
        "ok" : 0,
        "errmsg" : "Index with name: testBedName_1 already exists with different options",
        "code" : 85,
        "codeName" : "IndexOptionsConflict"
}
> db.fixedtestbeds.dropIndex("testBedName_1")
{ "nIndexesWas" : 2, "ok" : 1 }
> db.fixedtestbeds.createIndex({testBedName: 1}, {unique:true})
{
        "createdCollectionAutomatically" : false,
        "numIndexesBefore" : 1,
        "numIndexesAfter" : 2,
        "ok" : 1
}

db.getCollection("atsprojects").createIndex({ projectName: 1, projectPhase: 1 }, { unique: true });

db.treemetadatas.insertMany([
    { rootId: "GqPnT0_lpIVwZhrmG1mgm", creator: "linzhengyuan@ruijie.com.cn", visibility: "private", created: new Date() }
]);
