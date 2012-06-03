<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Home extends CI_Controller {

	public function index()
	{
      $data = array(
         'page_title' => 'Welcome to qbtd' 
      );
		$this->load->view('home_welcome', $data);
	}
}
