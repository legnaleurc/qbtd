<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>

<div class="row">

   <div class="span6">
      <h2>Login</h2>
      <form class="well" action="" method="post" accept-charset="utf-8">
         <label>Username: </label>
         <input class="span3 input-xlarge" type="text" name="id" placeholder="longin id">
         
         <label>Password: </label>
         <input class="span3" type="password" name="password" placeholder="your password">

         <button class="btn" type="submit">Login</button>
         <p><a href="">Forget Password ?</a></p>
      </form>
   </div>


   <div class="span6">
      <h2>Register</h2>
   </div>

</div>

<?php $this->load->view('footer');  ?>
