function update_page(data)
{
    console.log(data);
    document.getElementById("json").innerText = data;
}

let server = Server();
server.request(update_page, 'products_page');
