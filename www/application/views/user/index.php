<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>
<?php  $this->load->helper('url');  ?>

<div class="row">

   <div class="span6">
      <h2>Login</h2>
      <form class="well" action="<?php echo site_url('user/login/'); ?>" method="post" accept-charset="utf-8">
         <label>Username: </label>
         <input class="span3 " type="text" name="username" placeholder="longin id">
         
         <label>Password: </label>
         <input class="span3" type="password" name="password" placeholder="your password">

         <p><button class="btn" type="submit">Login</button>
         <a href="">Forget Password ?</a></p>
      </form>
   </div>


   <div class="span6">
      <h2>Register</h2>
      <form class="well" action="<?php echo site_url('user/login/'); ?>" method="post" accept-charset="utf-8">
         <label for="username">Username: </label>
         <input type="text" name="username" value="" id="username">

         <label for="email">Email</label>
         <input class="input-smail" type="text" name="email" value="" id="email">

         <label for="password">Password: </label>
         <input type="password" name="password" value="" id="password">

         <label for="ConfirmPassword">Confirm Password:</label>
         <input type="password" name="password2" value="" id="password2">
      
      <p><button class="btn" type=submit">Register</button></p>
      </form>
   </div>

</div>

<?php $this->load->view('footer');  ?>
