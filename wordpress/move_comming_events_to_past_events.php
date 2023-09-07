$args = array(
    'post_type' => 'post',
    'posts_per_page' => -1,
    'tax_query' => array(
        array(
            'taxonomy' => 'post_tag',
            'field'    => 'name',
            'terms'    => 'Nadchodzące',
        ),
        array(
            'taxonomy' => 'category',
            'field' => 'name',
            'terms' => 'Wydarzenia',
        ) ,
    )
);

$all_posts = new WP_Query($args);

if ($all_posts->have_posts()) {
    while ($all_posts->have_posts()) {
        $all_posts->the_post();
        
        $post_id = get_the_ID();		
        $post_title = get_the_title();
        $event_date_str = substr($post_title, 0, 10);
        $event_date = DateTime::createFromFormat('Y.m.d', $event_date_str);
        $current_date = new DateTime();
        
        if ($event_date == false || array_sum($event_date::getLastErrors())) {
            continue;
        }

        if ($event_date >= $current_date) {
            continue;
        }
        
        $current_tags = wp_get_post_tags($post_id, array('fields' => 'names'));
        $new_tags = array('Przeszłe');
        
        $indexToRemove = array_search("Nadchodzące", $current_tags);
        if ($indexToRemove !== false) {
            unset($current_tags[$indexToRemove]);
        }

        $tags_to_set = array_merge($current_tags, $new_tags);
        wp_set_post_tags($post_id, $tags_to_set);
    }
    wp_reset_postdata();
}
