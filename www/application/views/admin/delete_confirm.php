<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>
<?php  $this->load->helper('url');  ?>

<h2>User Management</h2>
<p style="margin-top: 25px;"> </p>

<div class="span6 pull-center alert alert-error">
<h3>Delete Confirm</h3>
<p>You are going to delete an account!</p>
<p>ID: <?php echo $target['id']; ?></p>
<p>User name: <?php echo $target['username']; ?></p>
<p>Email: <?php echo $target['email']; ?></p>
<p>
   <a class="btn btn-danger" href="<?php echo site_url('admin/deleteUser/'.$target['id'].'/confirmed');?>">Delete</a>
   <a class="btn" href="<?php echo site_url('admin/'); ?>">Cancel</a>
</p>
</div>

<?php $this->load->view('footer');  ?>
