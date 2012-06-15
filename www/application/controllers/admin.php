<?php

class Admin extends CI_Controller
{
   
   function __construct( )
   {
      parent::__construct();
      $this->load->helper('url');
      $this->load->spark('ion_auth/2.2.4');
      $user = $this->getUserInfo();
      if( $this->ion_auth->logged_in() == TRUE ){
         $user = $this->getUserInfo();
         if( $user['isAdmin'] == FALSE )
            redirect('user/');
      }else{
         redirect('');
      }
   }

   public function index()
   {
      $data['page_title'] = 'User Admin';
      $data['loggedin'] = true;
      $data['user'] =  $this->getUserInfo();
      $this->load->view('admin/home', $data);
   }

   private function getUserInfo($id=NULL)
   {
      $info = $this->ion_auth->user($id)->row();
      $groups = $this->ion_auth->get_users_groups()->result();
      $isAdmin = false;
      foreach ($groups as $group) {
         $list[] = $group->id;
         if( $group->id == 1 )
            $isAdmin = true;
      }
      $user =  array(
         'sn' => $info->id ,
         'id' => $info->username,
         'email' => $info->email,
         'groups' => $list,
         'isAdmin' => $isAdmin
      );
      return $user;
   }
}
