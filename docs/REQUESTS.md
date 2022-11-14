# Examples

Here are a few examples of using the worker to get, modify and delete data from our API.

## Getting a user, author, book or borrow

This example will show how to get a single user, however, for all other data types, you simply replace every instance of `user`.

```cpp
QString id = "enter user id here";

// Send the GET request to the API, the response will always be a string
QString response = worker->get("/users/" + id.toStdString());

// The `response_has_error` method will easily check if the response resulted in an error
// If the request was a success, `error` will be 0
// Otherwise it will be the HTTP status code
int error = worker->response_has_error(response);
if (error > 0) {
    // Do something with the error
    return;
}

// Parse the response string into a JSON object
QJsonDocument document = QJsonDocument::fromJson(response.toUtf8());
QJsonObject object = document.object();

// To easily get and set the properties, load the user object into a user class
User user; // For books, use Book, for authors use Author etc...
user.read(object);

// You will now be able to access (and modify) the user properties
// Such as `id`, `first_name` and `email_address`
user.id;
user.first_name = "New Name";
user.email_address;
```

The main difference when getting a different data type is the properties on the class.

## Getting a list of users, authors, books or borrows

This example will show how to parse a list (array) of users (once again this applies to all data types).

```cpp
// Send a request to `/users`, this will return a list of user objects
QString response = worker->get("/users");

// Check for error here, just like mentioned above

// Parse the response string into a JSON array
QJsonDocument document = QJsonDocument::fromJson(response.toUtf8());
QJsonArray array = document.array();

// Do whatever you need with the array
// I would recommended converting each item into a user and pushing it to a new vector
std::vector<User> users;
for (auto item : array) {
    QJsonObject object = item.toObject();
    User user;
    user.read(object);
    users.push_back(user);
}

// You now have a vector of user objects
```

## Creating a new user, author, book or borrow

For this example, you're likely more interested in learning how to borrow/issued a book, so I'll show that this time.

```cpp
// Prepare the borrow object to create
Borrow borrow;
borrow.book_id = "book id";
borrow.borrower_id = "user id";
borrow.issued_at = 0; // unix timestamp
borrow.issued_for = 0; // time in seconds

// Convert the borrow to a plain JSON object
QJsonObject object;
borrow.write(object); // Write data from borrow into the object
QJsonDocument document;
document.setObject(object);

// Now we are ready to send the data
QString response = worker->put("/borrows", document.toJson());
// If successful `response` will just be the borrow object
// Same as if you were to GET '/book/id'

// Check if an error occurred
int error = worker->response_has_error(response);
if (error > 0) {
    // 400 = missing data
    // 404 = book or borrower not found
    // 403 = you are not same user as borrower_id
    return;
}
```

```cpp
// Unrelated, but the due date can be calculated like so:
int due_date = borrow.issued_at + borrow.issued_for;
```

## Updating an existing data type

Updating an existing piece of data is extermely similar to creating them, this example will show how to update a book.

```cpp
// Existing book
Book book;

// Convert book to a plain JSON object
QJsonObject object;
book.write(object); // You could skip the book step and just manually insert the properties
QJsonDocument document;
document.setObject(object);

// Now we send the data
QString response = worker->post("/book/" + book.id.toStdString(), document.toJson());

// blah blah blah
```

## Deleting an existing user, author, book or borrow

Delete a piece of data from the database.
In the case of a borrow, "deleting" it would be the equivalent of the member returning it.

```cpp
// Existing borrow
Borrow borrow;

QString response = worker->remove("/borrows/" + borrow.id.toStdString());

int error = worker->response_has_error(response);
if (error > 0) {
    return;
}
```

## Real world example

Update the phone number of a user.

```cpp
// Get user ID from anywhere in the app
QString user_id = "";
std::string endpoint = "/users/" + user_id.toStdString();

// Ensure it exists first
QString get_response = worker->get(endpoint);

// Handle not found
int get_error = worker->response_has_error(get_response);
if (get_error > 0) return; // Show message box maybe

// Convert response into a user object
QJsonDocumet get_document = QJsonDocument::fromJson(get_response.toUtf8());
User user;
user.read(get_document.object());

// Change the phone number
user.phone_number = "022-111-9999";

// Create JSON string to send
QJsonObject post_object;
user.write(post_object);
QJsonDocument post_document(post_object);

// Send the POST request
QString post_response = worker->post(endpoint, post_document.toJson());

// Handle any error
int post_error = worker->response_has_error(post_response);
if (post_error > 0) return; // Show message box maybe
```
