<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>
<?php  $this->load->helper('url');  ?>

<h2>User Management</h2>
<p style="margin-top: 25px;"> </p>

<div class="well">

   <p>ID: <?php echo $info['id']; ?> </p>

   <p>Username: <?php echo $info['username']; ?> </p>

   <p>Email: <?php echo $info['email']; ?> </p>

</div>

<?php $this->load->view('footer');  ?>
