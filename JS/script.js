
let server = Server();
let pages = {
    'products_page': request_product_page,
    'main_page': request_main_page
};

function change_address(event)
{
    console.log(event.target.id);
    pages[event.target.id]();
}

// requests
function request_product_page()
{
    server.request(update_product_page, 'products_page');
}

function request_main_page()
{
    server.request(update_main_page, 'main_page');
}

// updates
function update_product_page(data)
{
    console.log(data);

    let html = '';
    data.products.forEach(function (element)
    {
        let product =
            '<h3>' + element.name + '</h3>' +
            '<p>' + element.description + '</p>';

        html += '<div>' + product + '</div>'
    });

    document.getElementById('json').innerHTML = html;
}

function update_main_page(data)
{
    console.log(data);

    let html = '';
    html += '<h1>' + data.title + '</h1>';
    html += '<p>' + data.description + '</p>';
    document.getElementById('json').innerHTML = html;
}


document.addEventListener("click", change_address);