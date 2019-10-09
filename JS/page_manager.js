function Page_Manager()
{
    // fields
    let requests = Request_Manager();

    // site pages
    let pages = {
        'main': requests.main_page,
        'products': requests.product_page,
        'contact': requests.contact_page,
    };

    // methods
    function change_address(event)
    {
        console.log('Page_Manager.change_address: ' + event.target.id);
        pages[event.target.id]();
    }

    function load_page(page)
    {
        console.log('Page_Manager.load_page: ' + page);
        pages[page]();
    }

    // set event listener
    document.addEventListener("click", change_address);

    // public methods
    return {
        load_page: load_page
    }
}