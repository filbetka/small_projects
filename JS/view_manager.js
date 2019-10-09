function View_Manager()
{
    // fields
    let content = document.getElementById('content');

    // methods
    function update_product_page(data)
    {
        let html = '';
        data.products.forEach(function (element) {
            let product =
                '<h3>' + element.name + '</h3>' +
                '<p>' + element.description + '</p>';

            html += '<div>' + product + '</div>'
        });

        content.innerHTML = html;
    }

    function update_main_page(data)
    {
        let html = '';
        html += '<h1>' + data.title + '</h1>';
        html += '<p>' + data.description + '</p>';
        content.innerHTML = html;
    }

    // public methods
    return {
        update_product_page: update_product_page,
        update_main_page: update_main_page
    }
}