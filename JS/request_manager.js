function Request_Manager()
{
    // fields
    let server = Server();
    let view = View_Manager();

    // methods
    function product_page()
    {
        server.request(view.update_product_page, 'products_page');
    }

    function main_page()
    {
        server.request(view.update_main_page, 'main_page');
    }

    // public methods
    return {
        product_page: product_page,
        main_page: main_page
    }
}
