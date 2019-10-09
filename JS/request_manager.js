function Request_Manager()
{
    // fields
    let server = Server();
    let view = View_Manager();

    // methods
    function product_page()
    {
        server.request(view.set_product_page, 'products_page');
    }

    function main_page()
    {
        server.request(view.set_main_page, 'main_page');
    }

    function contact_page()
    {
        server.request(view.set_contact_page, 'contact_page');
    }

    // public methods
    return {
        product_page: product_page,
        main_page: main_page,
        contact_page: contact_page,
    }
}
