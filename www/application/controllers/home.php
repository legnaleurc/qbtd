<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Home extends CI_Controller {

   public function __construct()
   {
      parent::__construct();
      $this->load->helper('url');
      $this->load->spark('ion_auth/2.2.4');
   }
	public function index()
	{
      // Check if user logged_in
      if( $this->ion_auth->logged_in() == true ){
         redirect('user/');
      }

      $data = array(
         'page_title' => 'Welcome to qbtd',
         'loggedin' => false
      );
		$this->load->view('home_welcome', $data);
	}
}
