<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class User extends CI_Controller {

	public function index()
	{
      $data = array(
         'page_title' => 'Login'
      );
      $this->load->view('user/index', $data);
	}

   public function login()
   {
   }

   public function register()
   {
   }

   public function checkID($id)
   {
      // code...
   }

   public function checkMail($mail)
   {
      // code...
   }
}
