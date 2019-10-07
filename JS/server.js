function Server()
{
    // map address to data
    let data = {

        'products_page': {
            products: [
                {
                    name: 'Backpack',
                    description: 'You can insert to that your laptop'
                },
                {
                    name: 'Guitar',
                    description: 'You can playing on the instrument your favourite songs'
                },
                {
                    name: 'Headphones',
                    description: 'You can listen your favourite songs'
                }
            ],
        },

        'main_page': {
            title: 'Your the best shop ever!',
            description: 'Oh..'
        }

    };

    // process client request
    function request(callback, address)
    {
        window.setTimeout(
            function ()
            {
                callback(data[address]);
            },
            1000
        )
    }

    return {
        request: request
    };
}
