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

let server = Server();
server.request(update_product_page, 'products_page');
//server.request(update_main_page, 'main_page');
