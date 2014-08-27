<?php

/**
 * @file
 * Defines all hooks and helper functions.
 */


/**
* Implementation of hook_menu()
*/
function rmcad_menu() {

    $items['ajax/curriculum'] = array(
        'title' => 'Curriculum',
        'page callback' => 'rmcad_curriculum',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['ajax/possibilities'] = array(
        'title' => 'Possibilities',
        'page callback' => 'rmcad_possibilities',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['ajax/events'] = array(
        'title' => 'Events',
        'page callback' => 'rmcad_events',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['ajax/social'] = array(
        'title' => 'Events',
        'page callback' => 'rmcad_social',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['social_overview'] = array(
        'title' => 'Social Overview',
        'page callback' => 'rmcad_social_overview',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['admin/settings/rmcad_social'] = array(
    'title' => 'Social Aggregator',
    'description' => 'Approve new items for site display',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('rmcad_social_admin'),
    'access arguments' => array('access administration pages'),
    'type' => MENU_NORMAL_ITEM,
   );

    $items['ajax/social_approve'] = array(
        'title' => 'Social Approve',
        'page callback' => 'rmcad_social_approve',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['ajax/submit_rfi'] = array(
        'title' => 'RFI',
        'page callback' => 'rmcad_submit_rfi',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['ajax/submit_contact'] = array(
        'title' => 'Contact',
        'page callback' => 'rmcad_submit_contact',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    $items['ajax/related_news'] = array(
        'title' => 'Related News',
        'page callback' => 'rmcad_related_news',
        'access callback' => TRUE,
        'type' => MENU_CALLBACK,
    );

    return $items;
}

function rmcad_curriculum($degree) {

	if(isset($degree))
		$nid = $degree;
	else
		$nid = $_GET['degree'];
	$node = node_load($nid);

	?>

	    <div id="academics-curriculum">
        	<div class="container clearfix">
            	<nav>
                	<h4><?php print $node->title; ?></h4>
                    <div id="academics-curriculum-nav-container">
                        <div id="academics-curriculum-nav-wrapper">
        					<?php foreach($node->field_degree_tracks['und'] as $track) {
        					    echo '<div class="first-level">';
        
        						//Degree Track Name
        						$track = node_load($track['nid']);
        						echo '<div class="title"><a href="#" class="section' . $track->nid . "\" onclick=\"_gaq.push(['_trackEvent', '". strtoupper($node->title) ."', 'click', '" . strtoupper($track->title) . "']);\">" . $track->title . '</a></div>';
        
        						//Load all class type taxonomy terms
        						$vocab = taxonomy_vocabulary_machine_name_load('class_type');
        						$vid = $vocab->vid;
        			                        $terms = taxonomy_get_tree($vid);
                                
        						echo '<ul class="sub-links">';
        						
        						foreach($terms as $term) {
        							echo '<li class="track' . $track->nid . 'section' . $term->tid . '"><a href="#track' . $track->nid . 'section' . $term->tid . '">' . $term->name . '</a></li>';
        						}
        						//End hidden divs
        						
        						echo '</ul></div>';
        					} ?>
        				</div>
        			</div>
				</nav>
				
		     	<section id="academics-curriculum-list">
	            	<header class="clearfix">
	                	<h6 class="class-name">Class Name</h6>
	                	<h6 class="credits">Credits</h6>
	             	</header>
					<div id="curriculum-list-wrapper">
					    <div id="curriculum-links">
    					<?php
    					    foreach($node->field_degree_tracks['und'] as $track) {
    					    
    					        //Degree Track Name
    							$track = node_load($track['nid']);
    
    							//Load all class type taxonomy terms
    							$vocab = taxonomy_vocabulary_machine_name_load('class_type');
    							$vid = $vocab->vid;
			    	                        $terms = taxonomy_get_tree($vid);
    	                        
    	                			        echo '<div id="section' . $track->nid . '">';
    					
    							//Load all classs into hidden div
    							foreach($terms as $term) {
								$hours = 0;		
								$classes = 0;
	
    								echo "\n" . '<article id="track' . $track->nid . 'section' . $term->tid . '">' . "\n"; 
    								echo '<ul>';
    								echo '<li class="title">' . $term->name; ?>
								<span id="hours-for-track<?= $track->nid ?>section<?= $term->tid ?>"></span>
								<?php 
								echo '</li>';
    								foreach($track->field_curriculum['und'] as $class) {
    									$class = node_load($class['nid']);
    									if($class->field_class_type['und'][0]['tid'] == $term->tid):
										$classes++;
										$hours += $class->field_credit_hours['und'][0]['value'];
    									?>
    									<li>
    										<p><?php print $class->title; ?></p>
    										<span><?php print $class->field_credit_hours['und'][0]['value']; ?></span>
    									</li>
    									<?php 
    									endif; 
    								}
    								echo "</ul>";
    								echo '</article>';

								if($classes == 0): ?>

									<script type="text/javascript">

										jQuery("#track<?= $track->nid ?>section<?= $term->tid ?>").hide();
										jQuery(".track<?= $track->nid ?>section<?= $term->tid ?>").hide();
										
										
									</script>

								<?php else: ?>
									<script type="text/javascript">
									jQuery("#hours-for-track<?= $track->nid ?>section<?= $term->tid ?>").html("<?= $hours ?> Total");
									</script>
								<? endif; 
    							}
    							
    							echo '</div>';
    							//End hidden divs
    					    } 
    					?>
    					</div>
					</div>
 	   				<!-- Remove temporarily
					<div class="total-credits">
			 	   		<strong><?php print $hours; ?></strong>
			 	   	    <em>Credit Hours</em>
			 	   	</div>
					-->
				</section>
				
				<aside>
				<?php print $node->field_curriculum_description['und'][0]['value']; ?>
		                </aside>
			</div>
		    </div>
		
		<?php

}

function rmcad_possibilities($degree) {

	if(isset($degree))
                $nid = $degree;
        else
                $nid = $_GET['degree'];
        $node = node_load($nid);

	?>

    <div id="academics-possibilities">
       <div class="container clearfix">
           <aside>
				<?php if(isset($node->field_possibilities_video['und'])):?>
					<iframe width="540" height="300" src="<?php print $node->field_possibilities_video['und'][0]['value']; ?>" frameborder="0" allowfullscreen></iframe>
				<?php else: 
					$img = $node->field_possibilities_image['und'][0]['filename'];
				?>
					<img width="540" height="300" src="/sites/default/files/possibilities/<?php print $img; ?>" alt=""/>
				<?php endif; ?>
				<h4><?php print $node->field_possibilities_headline['und'][0]['value']; ?></h4>
				<?php print $node->field_possibilities_description['und'][0]['value']; ?>
           </aside>
           <article>
               <h4>Potential Careers</h4>
               <ul class="clearfix">

		<?php foreach($node->field_potential_careers['und'] as $career): ?>
                	<li><?php print $career['value']; ?></li>
		<?php endforeach; ?>
		</ul>
           </article>
       </div>
    </div>






	<?php

}

function rmcad_events($page_num = 0) {

	$events = array();
	//limit 7

	$offset = 7*$page_num;

	$sql = "select n.nid, d.field_event_date_value from node n, field_data_field_event_date d where n.status = 1 and n.type = 'events' and n.nid = d.entity_id and d.field_event_date_value >= '" . date('Y-m-d') . "%' order by d.field_event_date_value asc limit $offset, 7";

	$result = db_query($sql);
	foreach($result as $row) {
		$events[] = node_load($row->nid);
	}

	//If odd number of events, add an extra event so display does not break
	if(sizeof($events) % 2 == 0)
		$events[] = node_load($row->nid);

	$count = 0;
?>

<div id="homepage-events-list">
	<?php foreach($events as $node): 
		$date = date('l, M jS', strtotime($node->field_event_date['und'][0]['value']));
		$img = $node->field_main_event_photo['und'][0]['uri'];
                $style = "nowatrmcad_calendar";
                $img = image_style_url($style, $img);

		if($count == 0):
	?>
    <div class="event featured clearfix">
        <aside>
            <h4><a href="<?php print drupal_lookup_path('alias',"node/".$node->nid); ?>"><?php print $node->title; ?></a></h4>
            <h6><?php print $date; ?></h6>
            <p><?php print strip_tags($node->body['und'][0]['value']); ?></p>
        </aside>
        <figure>
            <img alt="<?php print $node->title; ?>" src="<?php print $img; ?>" width="150" />
        </figure>
    </div>
	<?php else: ?>
	<?php if($count % 2 == 1): ?>
    <div class="event-container clearfix <?php if($count == 1): ?>first<?php endif; ?>">
	<?php endif; ?>
        <div class="event" title="<?php print $node->title; ?>">
            <h4><a href="<?php print drupal_lookup_path('alias',"node/".$node->nid); ?>"><?php print $node->title; ?></a></h4>
            <h6><?php print $date; ?></h6>
        </div>
    <?php if($count % 2 == 0): ?>
    </div>
	<?php endif; ?>
	
	<?php 
		endif; 
		$count++;
		endforeach;
	?>
    </div>

	<?php

}

function rmcad_social_overview() {

	global $user;
	if($user->uid < 1) {
		drupal_access_denied();
		exit();
	} else {
	}


	$sql = "SELECT * from social_instagram ORDER BY instagram_id DESC";
	$result = db_query($sql); ?>

	<div style="display:block; float:left; width:40%;">

	<?php
	foreach($result as $row): 
		$time = date('Y-m-d g:i a', $row->time);
	?>
		<div style="display:block; float:left; margin:10px; ">
		<a href="<?php print $row->instagram_link; ?>" target="_blank"><img src="<?php print $row->thumbnail; ?>" /></a><br>
		
		<input type="checkbox" onclick="approve('?instagram_id=<?php print $row->instagram_id; ?>')" <?php if($row->approve == "1"): ?> checked="checked" <?php endif; ?> />
		<b><?php print $row->instagram_user; ?></b><br> <?php print $time; ?>
		</div>

	<?php endforeach; ?>
	</div>

	<div style="display:block; float:left; width:40%;">
	<?php
	$sql = "SELECT * from social_twitter ORDER BY twitter_id DESC";
	$result = db_query($sql);
	foreach($result as $row): 
		$time = date('Y-m-d g:i a', $row->tweet_time);
	?>
		<div style="display:block; float:left; margin:10px; width:100%; ">
		<a href="http://twitter.com/<?php print $row->user_name; ?>/status/<?php print $row->twitter_id; ?>" target="_blank"><?php print $row->tweet; ?></a><br>
		<input type="checkbox" onclick="approve('?twitter_id=<?php print $row->twitter_id; ?>')" <?php if($row->approve == "1"): ?> checked="checked" <?php endif; ?> />
		<b><?php print $row->user_name; ?></b> <?php print $time; ?>
		</div>

	<?php endforeach; ?>
	</div>

	<script type="text/javascript" src="/misc/jquery.js?v=1.4.4"></script>
	<script type="text/javascript">

		function approve(id) {
			jQuery.get('/ajax/social_approve' + id);
		}

	</script>


	<?php
}

function rmcad_social_approve($id) {

	$table = "";
	$column = "";

	if(isset($_GET['twitter_id'])) {
		$id = $_GET['twitter_id'];
		$table = "social_twitter";
		$column = "twitter_id";
	} else if(isset($_GET['instagram_id'])) {
		$id = $_GET['instagram_id'];
		$table = "social_instagram";
		$column = "instagram_id";
	} else {
		header("HTTP/1.1 500 Internal Server Error");
		exit();
	}
	
	$sql = "UPDATE $table SET approve = IF(approve=1, 0, 1); WHERE $column = $id LIMIT 1";
	$result = db_update($table)
		->expression(
			'approve', 'IF(approve=1, 0, 1)'
		)
		->condition(
			$column, $id
		)
		->execute(); 
	

}

function rmcad_social_admin() {

  ob_start();
  rmcad_social_overview();
  $output = ob_get_clean();

  $form = array();

  /*$form['onthisdate_maxdisp'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of links'),
    '#default_value' => variable_get('onthisdate_maxdisp', 3),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t("The maximum number of links to display in the block."),
    '#required' => TRUE,
  );*/

  $form['iframecontent'] = array(
	'#markup' => $output,
  );

  $form = system_settings_form($form);

  unset($form['#submit']);
  unset($form['actions']);
	
  return $form;

}

function rmcad_social($page_num) {

	if(isset($_GET['page_num']))
		$page_num = $_GET['page_num'];
	else
		$page_num = 0;	

	//echo "PAGE NUM: $page_num";

	$count = 3;
	$page_num = $page_num * $count;

	$sql = "SELECT * FROM social_instagram WHERE approve = 1 ORDER BY instagram_id DESC LIMIT $page_num, $count";
	//echo $sql;
	$result = db_query($sql);
	$instagrams = array();
	foreach($result as $row) {
		$instagrams[] = $row;
	}

	$sql = "SELECT * FROM social_twitter WHERE approve = 1 ORDER BY twitter_id DESC LIMIT $page_num, $count";
	//echo $sql;
	$result = db_query($sql);
	$tweets = array();
	foreach($result as $row) {
		$tweets[] = $row;
	}
	?>

	<!-- TEMP SOCIAL FEED FIX -->
	<div class="clearfix active" id="homepage-activity-social">
	    <div class="item twitter">
		<header class="item-title">
		    <h6>Twitter</h6>
		</header>
		<div class="item-content">
		    <em><?php print $tweets[0]->tweet; ?></em>
		    <cite>&mdash; <a href="https://twitter.com/<?php print $tweets[0]->user_name; ?>" target="_blank">@<?php print $tweets[0]->user_name; ?></a></cite>
		</div>
	    </div>
	    <div class="item instagram">
		<header class="item-title">
		    <h6>Instagram</h6>
		</header>
		<div class="item-content">
		    <a target="_blank" href="<?php print $instagrams[0]->instagram_link; ?>"><img alt="Photo Title" height="150" src="<?php print $instagrams[0]->thumbnail; ?>" width="150" /></a>
		    <cite>&mdash; <a target="_blank" href="http://instagram.com/<?php print $instagrams[0]->instagram_user; ?>/">@<?php print $instagrams[0]->instagram_user; ?></a></cite>
		</div>
	    </div>
	    <div class="item twitter last">
		<header class="item-title">
		    <h6>Twitter</h6>
		</header>
		<div class="item-content">
		    <em><?php print $tweets[1]->tweet; ?></em>
		    <cite>&mdash; <a href="https://twitter.com/<?php print $tweets[1]->user_name; ?>" target="_blank">@<?php print $tweets[1]->user_name; ?></a></cite>
		</div>
	    </div>
	    <div class="item instagram">
		<header class="item-title">
		    <h6>Instagram</h6>
		</header>
		<div class="item-content">
		    <a target="_blank" href="<?php print $instagrams[1]->instagram_link; ?>"><img alt="Photo Title" height="150" src="<?php print $instagrams[1]->thumbnail; ?>" width="150" /></a>
		    <cite>&mdash; <a target="_blank" href="http://instagram.com/<?php print $instagrams[1]->instagram_user; ?>/">@<?php print $instagrams[1]->instagram_user; ?></a></cite>
		</div>
	    </div>
	    <div class="item twitter">
		<header class="item-title">
		    <h6>Twitter</h6>
		</header>
		<div class="item-content">
		    <em><?php print $tweets[2]->tweet; ?></em>
		    <cite>&mdash; <a href="https://twitter.com/<?php print $tweets[2]->user_name; ?>" target="_blank">@<?php print $tweets[2]->user_name; ?></a></cite>
		</div>
	    </div>
	    <div class="item instagram last">
		<header class="item-title">
		    <h6>Instagram</h6>
		</header>
		<div class="item-content">
		    <a target="_blank" href="<?php print $instagrams[2]->instagram_link; ?>"><img alt="Photo Title" height="150" src="<?php print $instagrams[2]->thumbnail; ?>" width="150" /></a>
		    <cite>&mdash; <a target="_blank" href="http://instagram.com/<?php print $instagrams[2]->instagram_user; ?>/">@<?php print $instagrams[2]->instagram_user; ?></a></cite>
		</div>
	    </div>
	</div>

	<?php
	
}


function stripslashes_deep($value) {
  $value = is_array($value) ?
    array_map('stripslashes_deep', $value) :
    stripslashes($value);

  return $value;
}

//Take input POST value and run against array. If there is a match
//between value and input the array key will be returned
function input_filter($input, $filter_array){
echo "Input Filter, input: $input\n";
	foreach ($filter_array as $key=>$value){
		echo "Key: $key, Value: $value\n";
		if($input == $key){
			echo "Found key $key\n";
			//return key of filter array that matches input
			return $key;
		}
	}
}

function rmcad_submit_rfi() {

	//Check captcha token
	if(isset($_POST['source'])) {

		if($_POST['source'] != "569efee60c1ae9304d4408d4adef5269") 
			exit("Invalid source token");
	
	} else {
		exit("Invalid source token");
	}

	//State conversion filter array
	$state_list = array(
				'AL'=>"Alabama",
		    'AK'=>"Alaska",  
		    'AZ'=>"Arizona",  
		    'AR'=>"Arkansas",  
		    'CA'=>"California",  
		    'CO'=>"Colorado",  
		    'CT'=>"Connecticut",  
		    'DE'=>"Delaware",  
		    'DC'=>"District Of Columbia",  
		    'FL'=>"Florida",  
		    'GA'=>"Georgia",  
		    'HI'=>"Hawaii",  
		    'ID'=>"Idaho",  
		    'IL'=>"Illinois",  
		    'IN'=>"Indiana",  
		    'IA'=>"Iowa",  
		    'KS'=>"Kansas",  
		    'KY'=>"Kentucky",  
		    'LA'=>"Louisiana",  
		    'ME'=>"Maine",  
		    'MD'=>"Maryland",  
		    'MA'=>"Massachusetts",  
		    'MI'=>"Michigan",  
		    'MN'=>"Minnesota",  
		    'MS'=>"Mississippi",  
		    'MO'=>"Missouri",  
		    'MT'=>"Montana",
		    'NE'=>"Nebraska",
		    'NV'=>"Nevada",
		    'NH'=>"New Hampshire",
		    'NJ'=>"New Jersey",
		    'NM'=>"New Mexico",
		    'NY'=>"New York",
		    'NC'=>"North Carolina",
		    'ND'=>"North Dakota",
		    'OH'=>"Ohio",  
		    'OK'=>"Oklahoma",  
		    'OR'=>"Oregon",  
		    'PA'=>"Pennsylvania",  
		    'RI'=>"Rhode Island",  
		    'SC'=>"South Carolina",  
		    'SD'=>"South Dakota",
		    'TN'=>"Tennessee",  
		    'TX'=>"Texas",  
		    'UT'=>"Utah",  
		    'VT'=>"Vermont",  
		    'VA'=>"Virginia",  
		    'WA'=>"Washington",  
		    'WV'=>"West Virginia",  
		    'WI'=>"Wisconsin",  
		    'WY'=>"Wyoming"
		    );

	//Degree conversion filter array
	$degree_list = array(
				'167'=>'Animation',
				'168'=>'Art Education',
				'169'=>'Fine Arts',
				'170'=>'Game Art',
				'171'=>'Communications Design',
				'172'=>'Illustration',
				'173'=>'Interior Design',
				'177'=>'Undecided',
				'239'=>'Interior Design (Online)',
				'632'=>'Illustration (Online)',
				'1239'=>'Design Strategy + Innovation (MA)',
				'1240'=>'Education, Leadership + Emerging Technologies (MA)',
				'1289'=>'Default',
				'1540'=>'Graphic Design'
				);

	//Education conversion filter array
	$education_list = array(
				'SHS'=> 'Still in High School',
				'HS'=> 'High School Diploma or GED',
				'CLGJ'=> 'Some College (1-23 Credits)',
				'CLGS'=> 'Some College (24-47 Credits)',
				'AS'=> "Associate's Degree",
				'BS'=> "Bachelor's Degree",
				'MS'=> "Master's Degree",
				'PHD'=> 'Doctoral Degree'
				);
	 
	//Handle magic quotes                                                
	if (get_magic_quotes_gpc()) {
	  $unescaped_post_data = stripslashes_deep($_POST);
	} 
	else {
	  $unescaped_post_data = $_POST;
	}
	//Grab form data for use
	$form_data = json_decode($unescaped_post_data['data_json']);
	//echo "Post: " . print_r($unescaped_post_data);	

	//Store post values inside variables
	$degree = $_POST['degree'];
	$first_name = $_POST['first_name'];
	$last_name = $_POST['last_name'];
	$email = $_POST['email'];
	$phone = $_POST['phone'];
	$address = $_POST['address'];
	$city = $_POST['city'];
	$state = $_POST['state'];
	$zip = $_POST['zip_code'];
	$education_level = $_POST['education_level'];
	$hs_graduation_year = $_POST['hs_graduation_year'];
	$sourceid = $_POST['sourceid'];
	$clientdocumentid = $_POST['clientdocumentid'];
	$campus = $_POST['ddcampus'];

	if($clientdocumentid == "")
		$clientdocumentid = 134;

        if($degree == "")
		$degree = "177"; //Unknown

	//Campus Default
	if(!$campus){
	    $campus = 120;
	}


	//Override old default source id
	if($sourceid == '6BC1ED'){
	    $sourceid = 'C4DFFE';
	}

	//Converted variables
	$converted_state = input_filter($state, $state_list);
	$converted_education = input_filter($education_level, $education_list);
	$converted_degree = input_filter($degree, $degree_list);

	//Hard code true confirmation
	$confirmation = "1";

	//POST to this URL
	$url = 'http://post.leadwatchlive.com/post.aspx';

	//Attached post fields for the CURL request
	$post_vars ="txtFirstName=$first_name".
				"&txtLastName=$last_name".
				"&txtEmailAddress=$email".
				"&txtAddress1=$address".
				"&txtCity=$city".
				"&txtState=$converted_state".
				"&txtZipCode=$zip".
				"&txtPhone1=$phone".
				"&ddClientDegreeId=$converted_degree".
				"&EducationLevel_RMCADCustom=$converted_education".
				"&ddHSGradYearCustom=$hs_graduation_year".
				"&sourceId=$sourceid".
				"&ClientDocumentId=$clientdocumentid".
				"&chkSubmitConfirmation=$confirmation".
				"&ddCampus=$campus";

	$ch = curl_init($url);
	curl_setopt( $ch, CURLOPT_POST, 1);
	curl_setopt( $ch, CURLOPT_POSTFIELDS, $post_vars);
	curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, 1);
	curl_setopt( $ch, CURLOPT_HEADER, 0);
	curl_setopt( $ch, CURLOPT_RETURNTRANSFER, 1);
	$response = curl_exec($ch);

	$r = var_export($response, true);

	$time = date('l jS \of F Y h:i:s A');

	$file = "log.txt";

	$open = fopen(dirname(__FILE__) . "/" . $file, "a+"); //open the file, (log.txt)
	fwrite($open, "$time \n");
	fwrite($open, $r);
	fwrite($open, "\n \n");
	fclose($open);


}
	
function rmcad_related_news($nid) {

	$nodes = array();

	$nodes[] = node_load(247);
	$nodes[] = node_load(66);

	foreach($nodes as $node): 	

		$img = $node->field_image['und'][0]['uri'];
		$style = "news_thumbnail";
		$img = image_style_url($style, $img);		
	?>

	 <a href="<?php print drupal_lookup_path('alias',"node/".$node->nid); ?>">
	    <div class="related-text">
		<strong><?php print $node->title; ?></strong>
		<time>12:00 PM <em>to</em> 4:00 PM</time>
		<time>Monday, September 27th</time>
	    </div>
	    <img alt="" height="190" src="<?php print $img; ?>" width="270" />
	</a>

	<?php
	endforeach;

}

function rmcad_submit_contact() {

	//Check captcha token
	if(isset($_POST['source'])) {

		if($_POST['source'] != "569efee60c1ae9304d4408d4adef5269") 
			exit("Invalid source token");
	
	} else {
		exit("Invalid source token");
	}

	//Get Vars
	$data = array();
	foreach($_POST as $j => $k) {
		$data[$j] = $k;
	}

        $term = taxonomy_term_load($data['contact-option']);

	$recipients = array(
		0 => array('david@purplerockscissors.com', 'tiffany@purplerockscissors.com', 'rob@purplerockscissors.com'),
		10 => array('admissions@rmcad.edu', 'dhoblick@rmcad.edu', 'webmaster@rmcad.edu'),
		11 => array('careerservices@rmcad.edu', 'webmaster@rmcad.edu'),
		12 => array('lgarriquesbenrahou@rmcad.edu', 'webmaster@rmcad.edu'),
		13 => array('alatkins@rmcad.edu', 'webmaster@rmcad.edu'),
		14 => array('hruss@rmcad.edu', 'webmaster@rmcad.edu'),
		15 => array('tdybdahl@rmcad.edu', 'webmaster@rmcad.edu'),
		16 => array('cstell@rmcad.edu', 'webmaster@rmcad.edu'),
		17 => array('alatkins@rmcad.edu', 'webmaster@rmcad.edu'),
		18 => array('sitefeedback@rmcad.edu', 'webmaster@rmcad.edu'),
		19 => array('hrjobs@rmcad.edu', 'webmaster@rmcad.edu'),
		20 => array('kwachtel@rmcad.edu', 'dhoblick@rmcad.edu', 'webmaster@rmcad.edu'),
	);

	//Uncomment to test
	//$data['contact-option'] = 0;

	$to = $recipients[$data['contact-option']];
	$to[] = "rmcad@purplerockscissors.com";
	$to = implode(',', $to);
	$subject = $data['contact-subject'] . " [RMCAD Contact - " . $term->name . "]";

	$message = "<strong>Name:</strong> " . $data['contact-name'];
	$message .= "<br>";
	$message .= "<strong>Email:</strong> " . $data['contact-email'];
	$message .= "<br><br>";
	$message .= nl2br($data['contact-body']);

	// Send mail

	$headers = "MIME-Version: 1.0\r\n";
        $headers .= "Content-type: text/html; charset=UTF-8\r\n";
        $headers .= 'From: "RMCAD" <noreply@rmcad.edu> ' . "\r\n";


        mail($to, $subject, $message, $headers);



}