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

let server = Server();
server.request(update_product_page, 'products_page');
