function Page_Manager()
{
    // fields
    let requests = Request_Manager();

    // site pages
    let pages = {
        'products_page': requests.product_page,
        'main_page': requests.main_page
    };

    // methods
    function change_address(event) {
        console.log(event.target.id);
        pages[event.target.id]();
    }

    // set event listener
    document.addEventListener("click", change_address);

    // public methods
    return {
        //
    }
}