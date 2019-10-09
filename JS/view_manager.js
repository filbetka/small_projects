function View_Manager()
{
    // fields
    let content = document.getElementById('content');

    // methods
    function set_product_page(data)
    {
        let html = '';
        data.products.forEach(
            function (element)
            {
                let product =
                    '<h3>' + element.name + '</h3>' +
                    '<p>' + element.description + '</p>';

                html += '<div>' + product + '</div>'
            }
        );

        content.innerHTML = html;
    }

    function set_main_page(data)
    {
        let html = '';
        html += '<h1>' + data.title + '</h1>';
        html += '<p>' + data.description + '</p>';
        content.innerHTML = html;
    }

    function set_contact_page(data)
    {
        let html = '';
        html += '<h1>' + data.title + '</h1>';
        html += '<p>' + data.address + '</p>';
        html += '<p>' + data.postal_code + '</p>';
        html += '<p>' + data.city + '</p>';
        html += '<p>' + data.country + '</p>';
        content.innerHTML = html;
    }

    // public methods
    return {
        set_product_page: set_product_page,
        set_main_page: set_main_page,
        set_contact_page: set_contact_page,
    }
}