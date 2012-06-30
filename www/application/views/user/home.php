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
      <form class="well" action="<?php echo site_url('user/register/'); ?>" method="post" accept-charset="utf-8">
         <div id="username" class="control-group">
            <label for="username" class="control-label">Username: </label>
            <div id="" class="controls">
               <input type="text" name="username" value="" id="username">
               <span class="help-inline hide">Username has been used</span>
            </div>
         </div>

         <div id="email" class="control-group">
            <label for="email" class="control-label">Email</label>
            <div id="" class="controls">
               <input class="input-smail" type="text" name="email" value="" id="email">
               <span class="help-inline hide">Email has been used</span>
            </div>
         </div>

         <label for="password">Password: </label>
         <input type="password" name="password" value="" id="password">

         <div id="pwd-group" class="control-group">
            <label for="password2" class="control-label">Confirm Password:</label>
            <div id="" class="controls">
               <input type="password" name="password2" value="" id="password2">
               <span id="pwd-help" class="help-inline hide">Password not match</span>
            </div>
         </div>
      
      <p><button class="btn" type=submit">Register</button></p>
      </form>
   </div>

</div>

<?php $this->load->view('footer');  ?>
