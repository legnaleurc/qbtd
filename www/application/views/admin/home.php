<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>
<?php  $this->load->helper('url');  ?>

<h2>User Management</h2>
<p style="margin-top: 25px;"> </p>

<div class="tabbable">

   <ul class="nav nav-tabs ">
      <li class="active"><a href="#">General</a></li>
      <li><a href="#">Admin</a></li>
      <li>
         <form class="form-search admin-tabs-search" action="#" method="post" accept-charset="utf-8">
         <i class="icon-search admin-tabs-search-icon"></i><input class="" type="text" name="key" value="">
         </form>
      </li>
   </ul>

   <div class="tab-content">

      <table class="table" style="width: 100%;">
         <thead>
            <tr>
               <td>ID</td>
               <td>Username</td>
               <td>Email</td>
               <td>Action</td>
            </tr>
         </thead>

         <tbody>

            <?php foreach($users as $u): ?>
               <tr>
                  <td><?php echo $u->id; ?></td>
                  <td><?php echo $u->username; ?></td>
                  <td><?php echo $u->email; ?></td>
                  <td>Delete / Edit </td>
               </tr>
            <?php endforeach; ?>

         </tbody>
      </table>

   </div>
</div>

<?php $this->load->view('footer');  ?>
