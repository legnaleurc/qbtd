<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class User extends CI_Controller {

   public function __construct()
   {
      parent::__construct();
      $this->load->spark('ion_auth/2.2.4');
   }

	public function index()
	{
      $data = array(
         'page_title' => 'Login'
      );
      $this->load->view('user/index', $data);
	}

   public function login()
   {
      $this->load->library('form_validation');

      $username = $this->input->post('username');
      $password = $this->input->post('password');

      if( $this->ion_auth->login($username, $password) == true ){
         // Login success
         echo "Login successs";
      }else{
         // Login Failed
         echo "Login Failed. ID: $username";
      }

   }

   public function register()
   {
      $username = $this->input->post('username');
      $password = $this->input->post('password');
      $password2 = $this->input->post('password2');
      $email = $this->input->post('email');
      $profile = array();

      $result = $this->ion_auth->register($username, $password, $email, $profile, '');
      if( $result == true ){
         echo "New user: $username";
      }else{
         echo "Reg Failed";
      }
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
