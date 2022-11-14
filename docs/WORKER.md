# Worker

The worker class is simply a basic wrapper around our backend API. Each window must have a `worker` property if you want to be able to access the API via that screen.

## Creating a new window

When creating a new window, follow these steps to add access to the API.

- Add a public `Worker *worker;` field to the windows header file. (Make sure you incldue the `worker.h` file as well.)

- Within the source file, add `, worker(new Worker())` near the constructor to initialise the worker class. Your constructor code would look something like this:

```cpp
Window::Window()
  : QMainWindow()
  , worker(new Worker())
  , ui(new Ui::Window)
{
    ui->setupUi(this);
}
```

- Finally add `delete worker;` to the classes destructor (just like `delete ui;`).

## Setting the token

Āfter creating an instance of a window with a worker, but before showing it, ensure you set the access token for the worker. This would involve something like  this `window->worker->set_token(token);`. The token will usually be defined within the current windows own worker instance. `window->worker->set_token(this->worker->token);` (you don't need to include to `this->`, but this would help in distinguishing the different worker instances.)

Your code might look something like this:

```cpp
Window *window = new Window(this);
window->worker->set_token(this->worker->token);
window->show();
this->hide();
```

## Making a GET request

To make a simple `GET`, just use the `worker->get("/url");` method. This method will return a `QString`, which you must parse the JSON from in order to use.

Example:

```cpp
QString user_response = worker->get("/users/[user_id]");
QJsonDocument user_doc = QJsonDocument::fromJson(user_response.toUtf8());
QJsonObject user_object = users_doc.object();
```

`user_object` will be an object with a user structure, you may want to convert this into our own `User` class.

```cpp
User user;
user.read(user_object);
```

These also apply to `Author`, `Book`, and `Borrow`.

## Making a POST (or PUT) request

Similar to making a GET, expect that you pass a request body object.

```cpp
// Prepare the JSON document
QJsonObject new_user;
new_user.insert("first_name", "John");
QJsonDocument new_user_body;
new_user_body.setObject(new_user);

// Send the request
QString response = worker->post("/users/[user_id]", new_user_body.toJson());
```

The above example will change the first name of the user with the ID `[user_id]` to "John".

Refer to the documention within our server repository for a list of endpoints.
