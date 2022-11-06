import requests

def test_some_get() :
    get = requests.get("http://127.0.0.1:8000/get/a/b/c")
    assert(get.status_code == 200)
    #print("GET : ", get.status_code)
    return True

def test_some_post() :
    post = requests.post("http://127.0.0.1:8000/post/a/b/c")
    assert(post.status_code == 200)
    #print("POST : ", post.status_code)
    return True


if __name__ == "__main__" :
    print("GET", test_some_get())
    print("POST", test_some_post())